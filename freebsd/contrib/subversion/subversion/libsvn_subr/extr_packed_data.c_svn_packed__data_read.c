#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {int len; char* data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
struct TYPE_24__ {scalar_t__ private_data; } ;
typedef  TYPE_2__ svn_packed__int_stream_t ;
struct TYPE_25__ {TYPE_4__* first_byte_stream; TYPE_2__* first_int_stream; } ;
typedef  TYPE_3__ svn_packed__data_root_t ;
struct TYPE_26__ {struct TYPE_26__* next; } ;
typedef  TYPE_4__ svn_packed__byte_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_27__ {TYPE_2__* next; } ;
typedef  TYPE_5__ packed_int_private_t ;
typedef  scalar_t__ apr_uint64_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  create_bytes_stream_body (TYPE_3__*) ; 
 int /*<<< orphan*/  packed_byte_stream_length (TYPE_4__*) ; 
 int /*<<< orphan*/  packed_int_stream_length (TYPE_2__*) ; 
 int /*<<< orphan*/  read_byte_stream_structure (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  read_int_stream_structure (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ read_packed_uint (TYPE_1__*) ; 
 int /*<<< orphan*/  read_stream_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  read_stream_uint (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  svn_packed__create_int_stream (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* svn_packed__data_create_root (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_read_full (int /*<<< orphan*/ *,char*,int*) ; 
 TYPE_1__* svn_stringbuf_create_ensure (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unflatten_byte_stream (TYPE_4__*,TYPE_1__*,int*) ; 
 int /*<<< orphan*/  unflatten_int_stream (TYPE_2__*,TYPE_1__*,int*) ; 

svn_error_t *
svn_packed__data_read(svn_packed__data_root_t **root_p,
                      svn_stream_t *stream,
                      apr_pool_t *result_pool,
                      apr_pool_t *scratch_pool)
{
  apr_uint64_t i;
  apr_uint64_t count;

  svn_packed__int_stream_t *int_stream;
  svn_packed__byte_stream_t *byte_stream;
  svn_packed__data_root_t *root = svn_packed__data_create_root(result_pool);

  svn_stringbuf_t *compressed
    = svn_stringbuf_create_ensure(1024, scratch_pool);
  svn_stringbuf_t *uncompressed
    = svn_stringbuf_create_ensure(1024, scratch_pool);

  /* read tree structure */

  apr_uint64_t tree_struct_size;
  svn_stringbuf_t *tree_struct;

  SVN_ERR(read_stream_uint(stream, &tree_struct_size));
  tree_struct
    = svn_stringbuf_create_ensure((apr_size_t)tree_struct_size, scratch_pool);
  tree_struct->len = (apr_size_t)tree_struct_size;

  SVN_ERR(svn_stream_read_full(stream, tree_struct->data, &tree_struct->len));
  tree_struct->data[tree_struct->len] = '\0';

  /* reconstruct tree structure */

  count = read_packed_uint(tree_struct);
  for (i = 0; i < count; ++i)
    read_int_stream_structure(tree_struct,
                              svn_packed__create_int_stream(root, FALSE,
                                                                 FALSE));

  count = read_packed_uint(tree_struct);
  for (i = 0; i < count; ++i)
    read_byte_stream_structure(tree_struct,
                               create_bytes_stream_body(root),
                               root->first_int_stream);

  /* read sub-stream data from disk, unzip it and buffer it */

  for (int_stream = root->first_int_stream;
       int_stream;
       int_stream = ((packed_int_private_t*)int_stream->private_data)->next)
    {
      apr_size_t offset = 0;
      SVN_ERR(read_stream_data(stream,
                               packed_int_stream_length(int_stream),
                               uncompressed, compressed));
      unflatten_int_stream(int_stream, uncompressed, &offset);
    }

  for (byte_stream = root->first_byte_stream;
       byte_stream;
       byte_stream = byte_stream->next)
    {
      apr_size_t offset = 0;
      SVN_ERR(read_stream_data(stream,
                               packed_byte_stream_length(byte_stream),
                               uncompressed, compressed));
      unflatten_byte_stream(byte_stream, uncompressed, &offset);
    }

  *root_p = root;
  return SVN_NO_ERROR;
}
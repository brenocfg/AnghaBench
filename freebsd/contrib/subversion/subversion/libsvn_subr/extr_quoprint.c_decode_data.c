#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct decode_baton {int /*<<< orphan*/  output; int /*<<< orphan*/  buflen; int /*<<< orphan*/  buf; int /*<<< orphan*/  pool; } ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  decode_bytes (TYPE_1__*,char const*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 TYPE_1__* svn_stringbuf_create_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
decode_data(void *baton, const char *data, apr_size_t *len)
{
  struct decode_baton *db = baton;
  apr_pool_t *subpool;
  svn_stringbuf_t *decoded;
  apr_size_t declen;
  svn_error_t *err = SVN_NO_ERROR;

  /* Decode this block of data.  */
  subpool = svn_pool_create(db->pool);
  decoded = svn_stringbuf_create_empty(subpool);
  decode_bytes(decoded, data, *len, db->buf, &db->buflen);

  /* Write the output, clean up, go home.  */
  declen = decoded->len;
  if (declen != 0)
    err = svn_stream_write(db->output, decoded->data, &declen);
  svn_pool_destroy(subpool);
  return err;
}
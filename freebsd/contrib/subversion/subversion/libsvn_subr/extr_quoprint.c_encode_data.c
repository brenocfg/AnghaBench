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
struct encode_baton {int /*<<< orphan*/  output; int /*<<< orphan*/  linelen; int /*<<< orphan*/  pool; } ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  encode_bytes (TYPE_1__*,char const*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 TYPE_1__* svn_stringbuf_create_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
encode_data(void *baton, const char *data, apr_size_t *len)
{
  struct encode_baton *eb = baton;
  apr_pool_t *subpool = svn_pool_create(eb->pool);
  svn_stringbuf_t *encoded = svn_stringbuf_create_empty(subpool);
  apr_size_t enclen;
  svn_error_t *err = SVN_NO_ERROR;

  /* Encode this block of data and write it out.  */
  encode_bytes(encoded, data, *len, &eb->linelen);
  enclen = encoded->len;
  if (enclen != 0)
    err = svn_stream_write(eb->output, encoded->data, &enclen);
  svn_pool_destroy(subpool);
  return err;
}
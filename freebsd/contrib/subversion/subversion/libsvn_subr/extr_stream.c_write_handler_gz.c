#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  z_stream ;
typedef  void* uInt ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct zbaton {int /*<<< orphan*/  substream; TYPE_1__* out; int /*<<< orphan*/ * pool; } ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_3__ {scalar_t__ avail_in; int avail_out; int /*<<< orphan*/  msg; void* next_out; int /*<<< orphan*/ * next_in; int /*<<< orphan*/ * opaque; int /*<<< orphan*/  zfree; int /*<<< orphan*/  zalloc; } ;
typedef  int /*<<< orphan*/  Bytef ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  Z_DEFAULT_COMPRESSION ; 
 int /*<<< orphan*/  Z_NO_FLUSH ; 
 void* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int deflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int deflateInit (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_error__wrap_zlib (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_write (int /*<<< orphan*/ ,void*,int*) ; 
 int /*<<< orphan*/  zalloc ; 
 int /*<<< orphan*/  zfree ; 

__attribute__((used)) static svn_error_t *
write_handler_gz(void *baton, const char *buffer, apr_size_t *len)
{
  struct zbaton *btn = baton;
  apr_pool_t *subpool;
  void *write_buf;
  apr_size_t buf_size, write_len;
  int zerr;

  if (btn->out == NULL)
    {
      btn->out = apr_palloc(btn->pool, sizeof(z_stream));
      btn->out->zalloc = zalloc;
      btn->out->zfree = zfree;
      btn->out->opaque =  btn->pool;

      zerr = deflateInit(btn->out, Z_DEFAULT_COMPRESSION);
      SVN_ERR(svn_error__wrap_zlib(zerr, "deflateInit", btn->out->msg));
    }

  /* The largest buffer we should need is 0.1% larger than the
     compressed data, + 12 bytes. This info comes from zlib.h.  */
  buf_size = *len + (*len / 1000) + 13;
  subpool = svn_pool_create(btn->pool);
  write_buf = apr_palloc(subpool, buf_size);

  btn->out->next_in = (Bytef *) buffer;  /* Casting away const! */
  btn->out->avail_in = (uInt) *len;

  while (btn->out->avail_in > 0)
    {
      btn->out->next_out = write_buf;
      btn->out->avail_out = (uInt) buf_size;

      zerr = deflate(btn->out, Z_NO_FLUSH);
      SVN_ERR(svn_error__wrap_zlib(zerr, "deflate", btn->out->msg));
      write_len = buf_size - btn->out->avail_out;
      if (write_len > 0)
        SVN_ERR(svn_stream_write(btn->substream, write_buf, &write_len));
    }

  svn_pool_destroy(subpool);

  return SVN_NO_ERROR;
}
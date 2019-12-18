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
typedef  scalar_t__ uInt ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct zbaton {TYPE_1__* in; int /*<<< orphan*/  read_flush; void* read_buffer; int /*<<< orphan*/  substream; int /*<<< orphan*/  pool; } ;
typedef  scalar_t__ apr_size_t ;
struct TYPE_3__ {int avail_in; scalar_t__ avail_out; int /*<<< orphan*/  msg; void* next_in; int /*<<< orphan*/ * next_out; int /*<<< orphan*/  opaque; int /*<<< orphan*/  zfree; int /*<<< orphan*/  zalloc; } ;
typedef  int /*<<< orphan*/  Bytef ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int ZBUFFER_SIZE ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 void* apr_palloc (int /*<<< orphan*/ ,int) ; 
 int inflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int inflateInit (TYPE_1__*) ; 
 int /*<<< orphan*/  read_helper_gz (int /*<<< orphan*/ ,void*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error__wrap_zlib (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zalloc ; 
 int /*<<< orphan*/  zfree ; 

__attribute__((used)) static svn_error_t *
read_handler_gz(void *baton, char *buffer, apr_size_t *len)
{
  struct zbaton *btn = baton;
  int zerr;

  if (btn->in == NULL)
    {
      btn->in = apr_palloc(btn->pool, sizeof(z_stream));
      btn->in->zalloc = zalloc;
      btn->in->zfree = zfree;
      btn->in->opaque = btn->pool;
      btn->read_buffer = apr_palloc(btn->pool, ZBUFFER_SIZE);
      btn->in->next_in = btn->read_buffer;
      btn->in->avail_in = ZBUFFER_SIZE;

      SVN_ERR(read_helper_gz(btn->substream, btn->read_buffer,
                             &btn->in->avail_in, &btn->read_flush));

      zerr = inflateInit(btn->in);
      SVN_ERR(svn_error__wrap_zlib(zerr, "inflateInit", btn->in->msg));
    }

  btn->in->next_out = (Bytef *) buffer;
  btn->in->avail_out = (uInt) *len;

  while (btn->in->avail_out > 0)
    {
      if (btn->in->avail_in <= 0)
        {
          btn->in->avail_in = ZBUFFER_SIZE;
          btn->in->next_in = btn->read_buffer;
          SVN_ERR(read_helper_gz(btn->substream, btn->read_buffer,
                                 &btn->in->avail_in, &btn->read_flush));
        }

      /* Short read means underlying stream has run out. */
      if (btn->in->avail_in == 0)
        {
          *len = 0;
          return SVN_NO_ERROR;
        }

      zerr = inflate(btn->in, btn->read_flush);
      if (zerr == Z_STREAM_END)
        break;
      else if (zerr != Z_OK)
        return svn_error_trace(svn_error__wrap_zlib(zerr, "inflate",
                                                    btn->in->msg));
    }

  *len -= btn->in->avail_out;
  return SVN_NO_ERROR;
}
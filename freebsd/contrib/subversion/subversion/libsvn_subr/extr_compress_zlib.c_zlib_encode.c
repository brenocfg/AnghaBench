#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int len; unsigned long blocksize; scalar_t__* data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_uint64_t ;
typedef  int apr_size_t ;

/* Variables and functions */
 int MIN_COMPRESS_SIZE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int SVN__COMPRESSION_NONE ; 
 int SVN__MAX_ENCODED_UINT_LEN ; 
 int Z_OK ; 
 int /*<<< orphan*/  _ (char*) ; 
 int compress2 (unsigned char*,unsigned long*,unsigned char const*,int,int) ; 
 int svnCompressBound (int) ; 
 unsigned char* svn__encode_uint (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_error__wrap_zlib (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stringbuf_appendbytes (TYPE_1__*,char const*,int) ; 
 int /*<<< orphan*/  svn_stringbuf_ensure (TYPE_1__*,int) ; 
 int /*<<< orphan*/  svn_stringbuf_setempty (TYPE_1__*) ; 

__attribute__((used)) static svn_error_t *
zlib_encode(const char *data,
            apr_size_t len,
            svn_stringbuf_t *out,
            int compression_level)
{
  unsigned long endlen;
  apr_size_t intlen;
  unsigned char buf[SVN__MAX_ENCODED_UINT_LEN], *p;

  svn_stringbuf_setempty(out);
  p = svn__encode_uint(buf, (apr_uint64_t)len);
  svn_stringbuf_appendbytes(out, (const char *)buf, p - buf);

  intlen = out->len;

  /* Compression initialization overhead is considered to large for
     short buffers.  Also, if we don't actually want to compress data,
     ZLIB will produce an output no shorter than the input.  Hence,
     the DATA would directly appended to OUT, so we can do that directly
     without calling ZLIB before. */
  if (len < MIN_COMPRESS_SIZE || compression_level == SVN__COMPRESSION_NONE)
    {
      svn_stringbuf_appendbytes(out, data, len);
    }
  else
    {
      int zerr;

      svn_stringbuf_ensure(out, svnCompressBound(len) + intlen);
      endlen = out->blocksize;

      zerr = compress2((unsigned char *)out->data + intlen, &endlen,
                       (const unsigned char *)data, len,
                       compression_level);
      if (zerr != Z_OK)
        return svn_error_trace(svn_error__wrap_zlib(
                                 zerr, "compress2",
                                 _("Compression of svndiff data failed")));

      /* Compression didn't help :(, just append the original text */
      if (endlen >= len)
        {
          svn_stringbuf_appendbytes(out, data, len);
          return SVN_NO_ERROR;
        }
      out->len = endlen + intlen;
      out->data[out->len] = 0;
    }
  return SVN_NO_ERROR;
}
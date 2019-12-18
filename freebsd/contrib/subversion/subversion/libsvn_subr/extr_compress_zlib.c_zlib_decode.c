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
struct TYPE_4__ {int len; scalar_t__* data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int apr_uint64_t ;
typedef  int apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_SVNDIFF_INVALID_COMPRESSED_DATA ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int Z_OK ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,unsigned char const*,int) ; 
 unsigned char* svn__decode_uint (int*,unsigned char const*,unsigned char const*) ; 
 int /*<<< orphan*/  svn_error__wrap_zlib (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stringbuf_ensure (TYPE_1__*,int) ; 
 int uncompress (unsigned char*,unsigned long*,unsigned char const*,int) ; 

__attribute__((used)) static svn_error_t *
zlib_decode(const unsigned char *in, apr_size_t inLen, svn_stringbuf_t *out,
            apr_size_t limit)
{
  apr_size_t len;
  apr_uint64_t size;
  const unsigned char *oldplace = in;

  /* First thing in the string is the original length.  */
  in = svn__decode_uint(&size, in, in + inLen);
  len = (apr_size_t)size;
  if (in == NULL || len != size)
    return svn_error_create(SVN_ERR_SVNDIFF_INVALID_COMPRESSED_DATA, NULL,
                            _("Decompression of zlib compressed data failed: no size"));
  if (len > limit)
    return svn_error_create(SVN_ERR_SVNDIFF_INVALID_COMPRESSED_DATA, NULL,
                            _("Decompression of zlib compressed data failed: "
                              "size too large"));

  /* We need to subtract the size of the encoded original length off the
   *      still remaining input length.  */
  inLen -= (in - oldplace);
  if (inLen == len)
    {
      svn_stringbuf_ensure(out, len);
      memcpy(out->data, in, len);
      out->data[len] = 0;
      out->len = len;

      return SVN_NO_ERROR;
    }
  else
    {
      unsigned long zlen = len;
      int zerr;

      svn_stringbuf_ensure(out, len);
      zerr = uncompress((unsigned char *)out->data, &zlen, in, inLen);
      if (zerr != Z_OK)
        return svn_error_trace(svn_error__wrap_zlib(
                                 zerr, "uncompress",
                                 _("Decompression of svndiff data failed")));

      /* Zlib should not produce something that has a different size than the
         original length we stored. */
      if (zlen != len)
        return svn_error_create(SVN_ERR_SVNDIFF_INVALID_COMPRESSED_DATA,
                                NULL,
                                _("Size of uncompressed data "
                                  "does not match stored original length"));
      out->data[zlen] = 0;
      out->len = zlen;
    }
  return SVN_NO_ERROR;
}
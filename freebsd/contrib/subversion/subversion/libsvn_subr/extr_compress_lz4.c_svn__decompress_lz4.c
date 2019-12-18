#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int len; scalar_t__* data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ apr_uint64_t ;
typedef  scalar_t__ apr_size_t ;

/* Variables and functions */
 scalar_t__ INT_MAX ; 
 int LZ4_decompress_safe (char const*,scalar_t__*,int,int) ; 
 int /*<<< orphan*/  SVN_ERR_LZ4_DECOMPRESSION_FAILED ; 
 int /*<<< orphan*/  SVN_ERR_SVNDIFF_INVALID_COMPRESSED_DATA ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * _ (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,unsigned char const*,int) ; 
 unsigned char* svn__decode_uint (scalar_t__*,unsigned char const*,unsigned char const*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_ensure (TYPE_1__*,int) ; 
 int /*<<< orphan*/  svn_stringbuf_setempty (TYPE_1__*) ; 

svn_error_t *
svn__decompress_lz4(const void *data, apr_size_t len,
                    svn_stringbuf_t *out,
                    apr_size_t limit)
{
  apr_size_t hdrlen;
  int compressed_data_len;
  int decompressed_data_len;
  apr_uint64_t u64;
  const unsigned char *p = data;
  int rv;

  assert(len <= INT_MAX);
  assert(limit <= INT_MAX);

  /* First thing in the string is the original length.  */
  p = svn__decode_uint(&u64, p, p + len);
  if (p == NULL)
    return svn_error_create(SVN_ERR_SVNDIFF_INVALID_COMPRESSED_DATA, NULL,
                            _("Decompression of compressed data failed: "
                              "no size"));
  if (u64 > limit)
    return svn_error_create(SVN_ERR_SVNDIFF_INVALID_COMPRESSED_DATA, NULL,
                            _("Decompression of compressed data failed: "
                              "size too large"));
  decompressed_data_len = (int)u64;
  hdrlen = p - (const unsigned char *)data;
  compressed_data_len = (int)(len - hdrlen);

  svn_stringbuf_setempty(out);
  svn_stringbuf_ensure(out, decompressed_data_len);

  if (compressed_data_len == decompressed_data_len)
    {
      /* Data is in the original, uncompressed form. */
      memcpy(out->data, p, decompressed_data_len);
    }
  else
    {
      rv = LZ4_decompress_safe((const char *)p, out->data, compressed_data_len,
                               decompressed_data_len);
      if (rv < 0)
        return svn_error_create(SVN_ERR_LZ4_DECOMPRESSION_FAILED, NULL, NULL);

      if (rv != decompressed_data_len)
        return svn_error_create(SVN_ERR_SVNDIFF_INVALID_COMPRESSED_DATA,
                                NULL,
                                _("Size of uncompressed data "
                                  "does not match stored original length"));
    }

  out->data[decompressed_data_len] = 0;
  out->len = decompressed_data_len;

  return SVN_NO_ERROR;
}
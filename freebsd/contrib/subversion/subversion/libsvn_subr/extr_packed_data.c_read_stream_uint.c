#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int apr_uint64_t ;
typedef  int apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_CORRUPT_PACKED_DATA ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_read_full (int /*<<< orphan*/ *,char*,int*) ; 

__attribute__((used)) static svn_error_t *
read_stream_uint(svn_stream_t *stream, apr_uint64_t *result)
{
  apr_uint64_t shift = 0;
  apr_uint64_t value = 0;
  unsigned char c;

  do
    {
      apr_size_t len = 1;
      SVN_ERR(svn_stream_read_full(stream, (char *)&c, &len));
      if (len != 1)
        return svn_error_create(SVN_ERR_CORRUPT_PACKED_DATA, NULL,
                                _("Unexpected end of stream"));

      value += (apr_uint64_t)(c & 0x7f) << shift;
      shift += 7;
      if (shift > 64)
        return svn_error_create(SVN_ERR_CORRUPT_PACKED_DATA, NULL,
                                _("Integer representation too long"));
    }
  while (c >= 0x80);

  *result = value;
  return SVN_NO_ERROR;
}
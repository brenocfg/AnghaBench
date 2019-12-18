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
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
typedef  scalar_t__ svn_filesize_t ;
typedef  int /*<<< orphan*/  apr_uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT_NO_RETURN (int) ; 
 int SVN__MAX_ENCODED_UINT_LEN ; 
 unsigned char* svn__encode_uint (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stringbuf_appendbytes (int /*<<< orphan*/ *,char const*,int) ; 

__attribute__((used)) static void
append_encoded_int(svn_stringbuf_t *header, svn_filesize_t val)
{
  unsigned char buf[SVN__MAX_ENCODED_UINT_LEN], *p;

  SVN_ERR_ASSERT_NO_RETURN(val >= 0);
  p = svn__encode_uint(buf, (apr_uint64_t)val);
  svn_stringbuf_appendbytes(header, (const char *)buf, p - buf);
}
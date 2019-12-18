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
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_MD5_DIGESTSIZE ; 
 char const* svn__digest_to_cstring_display (unsigned char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

const char *
svn_md5_digest_to_cstring_display(const unsigned char digest[],
                                  apr_pool_t *pool)
{
  return svn__digest_to_cstring_display(digest, APR_MD5_DIGESTSIZE, pool);
}
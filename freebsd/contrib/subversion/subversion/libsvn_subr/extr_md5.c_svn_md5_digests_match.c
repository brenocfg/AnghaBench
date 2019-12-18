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
typedef  int /*<<< orphan*/  svn_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_MD5_DIGESTSIZE ; 
 int /*<<< orphan*/  svn__digests_match (unsigned char const*,unsigned char const*,int /*<<< orphan*/ ) ; 

svn_boolean_t
svn_md5_digests_match(const unsigned char d1[], const unsigned char d2[])
{
  return svn__digests_match(d1, d2, APR_MD5_DIGESTSIZE);
}
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
struct cgd_ioctl {char const* ci_disk; char const* ci_alg; char const* ci_ivmethod; int ci_keylen; char const* ci_key; int ci_blocksize; } ;
typedef  int /*<<< orphan*/  ci ;

/* Variables and functions */
 int /*<<< orphan*/  CGDIOCSET ; 
 int /*<<< orphan*/  memset (struct cgd_ioctl*,int /*<<< orphan*/ ,int) ; 
 int rump_sys_ioctl (int,int /*<<< orphan*/ ,struct cgd_ioctl*) ; 

__attribute__((used)) static int
configure_cgd(int fd, const char *dkpath, const char *alg,
    const char *ivmethod, const char *key, size_t keylen)
{
	struct cgd_ioctl ci;

	memset(&ci, 0, sizeof(ci));
	ci.ci_disk = dkpath;
	ci.ci_alg = alg;
	ci.ci_ivmethod = ivmethod;
	ci.ci_keylen = 8 * keylen - 8; /* Exclude the NUL terminator. */
	ci.ci_key = key;
	ci.ci_blocksize = 64;

	return rump_sys_ioctl(fd, CGDIOCSET, &ci);
}
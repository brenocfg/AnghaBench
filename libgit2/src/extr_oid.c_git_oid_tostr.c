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
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int GIT_OID_HEXSZ ; 
 int /*<<< orphan*/  git_oid_nfmt (char*,size_t,int /*<<< orphan*/  const*) ; 

char *git_oid_tostr(char *out, size_t n, const git_oid *oid)
{
	if (!out || n == 0)
		return "";

	if (n > GIT_OID_HEXSZ + 1)
		n = GIT_OID_HEXSZ + 1;

	git_oid_nfmt(out, n - 1, oid); /* allow room for terminating NUL */
	out[n - 1] = '\0';

	return out;
}
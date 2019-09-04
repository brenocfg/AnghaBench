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
 scalar_t__ GIT_OID_HEXSZ ; 
 char* git__malloc (scalar_t__) ; 
 int /*<<< orphan*/  git_oid_nfmt (char*,scalar_t__,int /*<<< orphan*/  const*) ; 

char *git_oid_allocfmt(const git_oid *oid)
{
	char *str = git__malloc(GIT_OID_HEXSZ + 1);
	if (!str)
		return NULL;
	git_oid_nfmt(str, GIT_OID_HEXSZ + 1, oid);
	return str;
}
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
 int /*<<< orphan*/  GIT_OID_HEXSZ ; 
 int git_oid_fromstrn (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

int git_oid_fromstr(git_oid *out, const char *str)
{
	return git_oid_fromstrn(out, str, GIT_OID_HEXSZ);
}
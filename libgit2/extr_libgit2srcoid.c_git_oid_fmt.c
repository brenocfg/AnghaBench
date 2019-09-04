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
 int /*<<< orphan*/  git_oid_nfmt (char*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

void git_oid_fmt(char *str, const git_oid *oid)
{
	git_oid_nfmt(str, GIT_OID_HEXSZ, oid);
}
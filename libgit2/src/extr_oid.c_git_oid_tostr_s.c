#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_2__ {char* oid_fmt; } ;

/* Variables and functions */
 TYPE_1__* GIT_GLOBAL ; 
 scalar_t__ GIT_OID_HEXSZ ; 
 int /*<<< orphan*/  git_oid_nfmt (char*,scalar_t__,int /*<<< orphan*/  const*) ; 

char *git_oid_tostr_s(const git_oid *oid)
{
	char *str = GIT_GLOBAL->oid_fmt;
	git_oid_nfmt(str, GIT_OID_HEXSZ + 1, oid);
	return str;
}
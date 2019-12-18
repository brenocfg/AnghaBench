#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct acl_entry {int dummy; } ;
struct acl {int /*<<< orphan*/  acl_cnt; int /*<<< orphan*/ * acl_entry; } ;
typedef  int /*<<< orphan*/  compare ;
typedef  TYPE_1__* acl_t ;
struct TYPE_3__ {struct acl ats_acl; } ;

/* Variables and functions */
 scalar_t__ _posix1e_acl_entry_compare ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void
_posix1e_acl_sort(acl_t acl)
{
	struct acl *acl_int;

	acl_int = &acl->ats_acl;

	qsort(&acl_int->acl_entry[0], acl_int->acl_cnt,
	    sizeof(struct acl_entry), (compare) _posix1e_acl_entry_compare);
}
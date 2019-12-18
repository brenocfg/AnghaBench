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
struct rrset_ref {int dummy; } ;
struct reply_info {int /*<<< orphan*/  rrset_count; int /*<<< orphan*/ * ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reply_info_sortref_cmp ; 

void 
reply_info_sortref(struct reply_info* rep)
{
	qsort(&rep->ref[0], rep->rrset_count, sizeof(struct rrset_ref),
		reply_info_sortref_cmp);
}
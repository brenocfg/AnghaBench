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
struct kinfo_proc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ORDERKEY_CPTICKS (struct kinfo_proc const*,struct kinfo_proc const*) ; 
 int /*<<< orphan*/  ORDERKEY_JID (struct kinfo_proc const*,struct kinfo_proc const*) ; 
 int /*<<< orphan*/  ORDERKEY_MEM (struct kinfo_proc const*,struct kinfo_proc const*) ; 
 int /*<<< orphan*/  ORDERKEY_PCTCPU (struct kinfo_proc const*,struct kinfo_proc const*) ; 
 int /*<<< orphan*/  ORDERKEY_PRIO (struct kinfo_proc const*,struct kinfo_proc const*) ; 
 int /*<<< orphan*/  ORDERKEY_RSSIZE (struct kinfo_proc const*,struct kinfo_proc const*) ; 
 int /*<<< orphan*/  ORDERKEY_STATE (struct kinfo_proc const*,struct kinfo_proc const*) ; 

__attribute__((used)) static int
compare_jid(const void *arg1, const void *arg2)
{
	const struct kinfo_proc *p1 = *(const struct kinfo_proc * const *)arg1;
	const struct kinfo_proc *p2 = *(const struct kinfo_proc * const *)arg2;

	ORDERKEY_JID(p1, p2);
	ORDERKEY_PCTCPU(p1, p2);
	ORDERKEY_CPTICKS(p1, p2);
	ORDERKEY_STATE(p1, p2);
	ORDERKEY_PRIO(p1, p2);
	ORDERKEY_RSSIZE(p1, p2);
	ORDERKEY_MEM(p1, p2);

	return (0);
}
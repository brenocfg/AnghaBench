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
typedef  scalar_t__ u64 ;
struct rmid_entry {int /*<<< orphan*/  rmid; } ;

/* Variables and functions */
 int /*<<< orphan*/  QOS_L3_OCCUP_EVENT_ID ; 
 scalar_t__ __rmid_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ resctrl_cqm_threshold ; 

__attribute__((used)) static bool rmid_dirty(struct rmid_entry *entry)
{
	u64 val = __rmid_read(entry->rmid, QOS_L3_OCCUP_EVENT_ID);

	return val >= resctrl_cqm_threshold;
}
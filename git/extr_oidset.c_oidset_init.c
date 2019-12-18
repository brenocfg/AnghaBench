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
struct oidset {int /*<<< orphan*/  set; } ;

/* Variables and functions */
 int /*<<< orphan*/  kh_resize_oid_set (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void oidset_init(struct oidset *set, size_t initial_size)
{
	memset(&set->set, 0, sizeof(set->set));
	if (initial_size)
		kh_resize_oid_set(&set->set, initial_size);
}
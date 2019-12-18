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
 int /*<<< orphan*/  kh_release_oid_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oidset_init (struct oidset*,int /*<<< orphan*/ ) ; 

void oidset_clear(struct oidset *set)
{
	kh_release_oid_set(&set->set);
	oidset_init(set, 0);
}
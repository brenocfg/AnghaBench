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
struct sb_info {scalar_t__ prio; } ;
struct sb_chinfo {struct sb_info* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */

__attribute__((used)) static int
sb16chan_resetdone(kobj_t obj, void *data)
{
	struct sb_chinfo *ch = data;
	struct sb_info *sb = ch->parent;

	sb->prio = 0;

	return 0;
}
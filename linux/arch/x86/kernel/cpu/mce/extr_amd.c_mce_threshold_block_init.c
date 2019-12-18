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
struct threshold_block {int /*<<< orphan*/  threshold_limit; } ;
struct thresh_restart {int set_lvt_off; int lvt_off; struct threshold_block* b; } ;

/* Variables and functions */
 int /*<<< orphan*/  THRESHOLD_MAX ; 
 int /*<<< orphan*/  threshold_restart_bank (struct thresh_restart*) ; 

__attribute__((used)) static void mce_threshold_block_init(struct threshold_block *b, int offset)
{
	struct thresh_restart tr = {
		.b			= b,
		.set_lvt_off		= 1,
		.lvt_off		= offset,
	};

	b->threshold_limit		= THRESHOLD_MAX;
	threshold_restart_bank(&tr);
}
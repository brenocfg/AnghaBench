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
struct TYPE_3__ {int /*<<< orphan*/  (* set_multiple ) (TYPE_1__*,unsigned long*,unsigned long*) ;} ;

/* Variables and functions */
 TYPE_1__* lubbock_misc_wr_gc ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,unsigned long*,unsigned long*) ; 

__attribute__((used)) static void lubbock_set_misc_wr(unsigned int mask, unsigned int set)
{
	unsigned long m = mask, v = set;
	lubbock_misc_wr_gc->set_multiple(lubbock_misc_wr_gc, &m, &v);
}
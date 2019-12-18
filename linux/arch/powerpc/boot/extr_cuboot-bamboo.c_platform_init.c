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
struct TYPE_2__ {int /*<<< orphan*/  bi_enet1addr; int /*<<< orphan*/  bi_enetaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CUBOOT_INIT () ; 
 int /*<<< orphan*/  bamboo_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__ bd ; 

void platform_init(unsigned long r3, unsigned long r4, unsigned long r5,
		unsigned long r6, unsigned long r7)
{
	CUBOOT_INIT();
	bamboo_init(&bd.bi_enetaddr, &bd.bi_enet1addr);
}
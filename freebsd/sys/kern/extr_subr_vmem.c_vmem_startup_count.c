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
struct vmem_btag {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_MAXALLOC ; 
 int UMA_SLAB_SPACE ; 
 int howmany (int /*<<< orphan*/ ,int) ; 

int
vmem_startup_count(void)
{

	return (howmany(BT_MAXALLOC,
	    UMA_SLAB_SPACE / sizeof(struct vmem_btag)));
}
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
struct gmap {int /*<<< orphan*/  asce; } ;

/* Variables and functions */
 scalar_t__ MACHINE_HAS_IDTE ; 
 int /*<<< orphan*/  __tlb_flush_global () ; 
 int /*<<< orphan*/  __tlb_flush_idte (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gmap_flush_tlb(struct gmap *gmap)
{
	if (MACHINE_HAS_IDTE)
		__tlb_flush_idte(gmap->asce);
	else
		__tlb_flush_global();
}
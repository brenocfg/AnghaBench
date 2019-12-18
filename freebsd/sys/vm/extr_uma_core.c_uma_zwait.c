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
typedef  int /*<<< orphan*/  uma_zone_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_WAITOK ; 
 void* uma_zalloc_arg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,void*) ; 

void
uma_zwait(uma_zone_t zone)
{
	void *item;

	item = uma_zalloc_arg(zone, NULL, M_WAITOK);
	uma_zfree(zone, item);
}
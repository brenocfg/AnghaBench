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
typedef  int /*<<< orphan*/  video_adapter_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/ * biosadapter ; 
 int biosadapters ; 
 int /*<<< orphan*/  probe_adapters () ; 

__attribute__((used)) static int
vga_probe(int unit, video_adapter_t **adpp, void *arg, int flags)
{
    probe_adapters();
    if (unit >= biosadapters)
	return ENXIO;

    *adpp = &biosadapter[unit];

    return 0;
}
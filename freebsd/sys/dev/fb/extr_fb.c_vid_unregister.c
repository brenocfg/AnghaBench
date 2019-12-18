#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t va_index; } ;
typedef  TYPE_1__ video_adapter_t ;

/* Variables and functions */
 int ENOENT ; 
 TYPE_1__** adapter ; 
 size_t adapters ; 
 int /*<<< orphan*/ ** vidsw ; 

int
vid_unregister(video_adapter_t *adp)
{
	if ((adp->va_index < 0) || (adp->va_index >= adapters))
		return ENOENT;
	if (adapter[adp->va_index] != adp)
		return ENOENT;

	adapter[adp->va_index] = NULL;
	vidsw[adp->va_index] = NULL;
	return 0;
}
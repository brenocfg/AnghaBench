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
struct TYPE_3__ {char* va_name; int va_type; int va_unit; scalar_t__ va_flags; } ;
typedef  TYPE_1__ video_adapter_t ;

/* Variables and functions */

void
vid_init_struct(video_adapter_t *adp, char *name, int type, int unit)
{
	adp->va_flags = 0;
	adp->va_name = name;
	adp->va_type = type;
	adp->va_unit = unit;
}
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
typedef  int /*<<< orphan*/  video_adapter_t ;
struct TYPE_2__ {int (* splash ) (int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 int ENODEV ; 
 TYPE_1__* splash_decoder ; 
 int stub1 (int /*<<< orphan*/ *,int) ; 

int
splash(video_adapter_t *adp, int on)
{
	if (splash_decoder != NULL)
		return (*splash_decoder->splash)(adp, on);
	return ENODEV;
}
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
struct TYPE_2__ {int (* set_hw_cursor_shape ) (int /*<<< orphan*/ *,int,int,int,int) ;} ;

/* Variables and functions */
 TYPE_1__* prevvidsw ; 
 int stub1 (int /*<<< orphan*/ *,int,int,int,int) ; 

__attribute__((used)) static int
s3lfb_set_hw_cursor_shape(video_adapter_t *adp, int base, int height,
			 int celsize, int blink)
{
	return (*prevvidsw->set_hw_cursor_shape)(adp, base, height,
			celsize, blink);
}
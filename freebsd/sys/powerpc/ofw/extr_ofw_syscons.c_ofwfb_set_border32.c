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
 int ofwfb_blank_display32 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
ofwfb_set_border32(video_adapter_t *adp, int border)
{
	/* XXX Be lazy for now and blank entire screen */
	return (ofwfb_blank_display32(adp, border));
}
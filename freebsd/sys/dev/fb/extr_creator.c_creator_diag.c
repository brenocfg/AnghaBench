#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_info_t ;
struct TYPE_6__ {int /*<<< orphan*/  va_name; } ;
typedef  TYPE_1__ video_adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  creator_get_info (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fb_dump_adp_info (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  fb_dump_mode_info (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
creator_diag(video_adapter_t *adp, int level)
{
	video_info_t info;

	fb_dump_adp_info(adp->va_name, adp, level);
	creator_get_info(adp, 0, &info);
	fb_dump_mode_info(adp->va_name, adp, &info, level);
	return (0);
}
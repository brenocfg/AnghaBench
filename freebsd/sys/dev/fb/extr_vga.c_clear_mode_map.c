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
struct TYPE_3__ {int vi_flags; } ;
typedef  TYPE_1__ video_info_t ;
typedef  int /*<<< orphan*/  video_adapter_t ;
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int V_INFO_COLOR ; 
 scalar_t__ vga_get_info (int /*<<< orphan*/ *,int,TYPE_1__*) ; 

__attribute__((used)) static void
clear_mode_map(video_adapter_t *adp, u_char *map[], int max, int color)
{
    video_info_t info;
    int i;

    /*
     * NOTE: we don't touch `bios_vmode[]' because it is shared
     * by all adapters.
     */
    for(i = 0; i < max; ++i) {
	if (vga_get_info(adp, i, &info))
	    continue;
	if ((info.vi_flags & V_INFO_COLOR) != color)
	    map[i] = NULL;
    }
}
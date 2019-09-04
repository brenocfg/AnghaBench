#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  tab_bar_hidden; } ;
struct TYPE_11__ {int num_tabs; scalar_t__ viewport_height; scalar_t__ viewport_width; TYPE_1__* fonts_data; } ;
struct TYPE_10__ {scalar_t__ bottom; scalar_t__ right; scalar_t__ top; scalar_t__ left; } ;
struct TYPE_9__ {scalar_t__ cell_height; } ;
typedef  TYPE_2__ Region ;
typedef  TYPE_3__ OSWindow ;

/* Variables and functions */
 int OPT (int /*<<< orphan*/ ) ; 
#define  TOP_EDGE 128 
 TYPE_8__ global_state ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tab_bar_edge ; 
 int /*<<< orphan*/  tab_bar_min_tabs ; 

void
os_window_regions(OSWindow *os_window, Region *central, Region *tab_bar) {
    if (!global_state.tab_bar_hidden && os_window->num_tabs >= OPT(tab_bar_min_tabs)) {
        switch(OPT(tab_bar_edge)) {
            case TOP_EDGE:
                central->left = 0; central->top = os_window->fonts_data->cell_height; central->right = os_window->viewport_width - 1;
                central->bottom = os_window->viewport_height - 1;
                tab_bar->left = central->left; tab_bar->right = central->right; tab_bar->top = 0;
                tab_bar->bottom = central->top - 1;
                break;
            default:
                central->left = 0; central->top = 0; central->right = os_window->viewport_width - 1;
                central->bottom = os_window->viewport_height - os_window->fonts_data->cell_height - 1;
                tab_bar->left = central->left; tab_bar->right = central->right; tab_bar->top = central->bottom + 1;
                tab_bar->bottom = os_window->viewport_height - 1;
                break;
        }
    } else {
        memset(tab_bar, 0, sizeof(Region));
        central->left = 0; central->top = 0; central->right = os_window->viewport_width - 1;
        central->bottom = os_window->viewport_height - 1;
    }
}
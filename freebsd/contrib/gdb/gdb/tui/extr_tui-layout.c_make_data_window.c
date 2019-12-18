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
struct tui_win_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOX_WINDOW ; 
 int /*<<< orphan*/  DATA_WIN ; 
 int /*<<< orphan*/  init_and_make_win (void**,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tui_term_width () ; 

__attribute__((used)) static void
make_data_window (struct tui_win_info * * win_info_ptr, int height, int origin_y)
{
  init_and_make_win ((void **) win_info_ptr,
		   DATA_WIN,
		   height,
		   tui_term_width (),
		   0,
		   origin_y,
		   BOX_WINDOW);
}
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
typedef  int /*<<< orphan*/  WINDOW ;

/* Variables and functions */
 int /*<<< orphan*/  color_default ; 
 int /*<<< orphan*/  draw_header (int /*<<< orphan*/ *,char*,char*,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
clear_confdlg_status_bar (WINDOW * win, int y, int x, int w)
{
  draw_header (win, "", "%s", y, x, w + 1, color_default);
}
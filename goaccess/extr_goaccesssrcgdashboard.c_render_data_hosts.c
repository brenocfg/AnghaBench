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
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_3__ {int /*<<< orphan*/  w; int /*<<< orphan*/  y; } ;
typedef  TYPE_1__ GDashRender ;

/* Variables and functions */
 int /*<<< orphan*/  color_selected ; 
 int /*<<< orphan*/  draw_header (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* left_pad_str (char*,int) ; 

__attribute__((used)) static void
render_data_hosts (WINDOW * win, GDashRender render, char *value, int x)
{
  char *padded_data;

  padded_data = left_pad_str (value, x);
  draw_header (win, padded_data, "%s", render.y, 0, render.w, color_selected);
  free (padded_data);
}
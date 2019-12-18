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
struct nk_vec2 {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct nk_rect {int member_2; int member_3; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct nk_command_buffer {int dummy; } ;
struct nk_color {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nk_fill_circle (struct nk_command_buffer*,struct nk_rect,struct nk_color) ; 
 struct nk_color nk_rgb (int,int,int) ; 

void draw_marker(struct nk_command_buffer* canvas, int lead, struct nk_vec2 pos)
{
    struct nk_color colors[4] = { nk_rgb(255,0,0), nk_rgb(255,255,0), nk_rgb(0,255,0), nk_rgb(0,96,255) };
    struct nk_rect rect = { -5 + pos.x, -5 + pos.y, 10, 10 };
    nk_fill_circle(canvas, rect, colors[lead]);
}
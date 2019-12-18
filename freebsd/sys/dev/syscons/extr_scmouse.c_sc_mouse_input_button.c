#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char mouse_pos; char xsize; } ;
typedef  TYPE_1__ scr_stat ;

/* Variables and functions */
 int /*<<< orphan*/  sc_respond (TYPE_1__*,char*,int,int) ; 

__attribute__((used)) static void
sc_mouse_input_button(scr_stat *scp, int button)
{
	char mouseb[6] = "\x1B[M";

	mouseb[3] = ' ' + button;
	mouseb[4] = '!' + scp->mouse_pos % scp->xsize;
	mouseb[5] = '!' + scp->mouse_pos / scp->xsize;
	sc_respond(scp, mouseb, sizeof mouseb, 1);
}
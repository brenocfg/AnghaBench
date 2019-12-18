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
typedef  int /*<<< orphan*/  scr_stat ;

/* Variables and functions */
 int /*<<< orphan*/  cut_buffer ; 
 int /*<<< orphan*/  sc_paste (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

void
sc_mouse_paste(scr_stat *scp)
{
    sc_paste(scp, cut_buffer, strlen(cut_buffer));
}
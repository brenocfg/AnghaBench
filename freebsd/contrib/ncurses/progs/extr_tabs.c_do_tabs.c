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

/* Variables and functions */
 int max_cols ; 
 int /*<<< orphan*/  putch ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  set_tab ; 
 int /*<<< orphan*/  tparm (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tputs (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_tabs(int *tab_list)
{
    int last = 1;
    int stop;

    putchar('\r');
    while ((stop = *tab_list++) > 0) {
	if (last < stop) {
	    while (last++ < stop) {
		if (last > max_cols)
		    break;
		putchar(' ');
	    }
	}
	if (stop <= max_cols) {
	    tputs(tparm(set_tab, stop), 1, putch);
	    last = stop;
	} else {
	    break;
	}
    }
    putchar('\n');
}
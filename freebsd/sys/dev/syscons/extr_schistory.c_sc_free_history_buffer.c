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
struct TYPE_3__ {int /*<<< orphan*/ * history; } ;
typedef  TYPE_1__ scr_stat ;
typedef  int /*<<< orphan*/  sc_vtb_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  SC_HISTORY_SIZE ; 
 int extra_history_size ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int imax (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sc_vtb_destroy (int /*<<< orphan*/ *) ; 
 int sc_vtb_rows (int /*<<< orphan*/ *) ; 

void
sc_free_history_buffer(scr_stat *scp, int prev_ysize)
{
	sc_vtb_t *history;
	int cur_lines;				/* current buffer size */
	int min_lines;				/* guaranteed buffer size */

	history = scp->history;
	scp->history = NULL;
	if (history == NULL)
		return;

	cur_lines = sc_vtb_rows(history);
	min_lines = imax(SC_HISTORY_SIZE, prev_ysize);
	extra_history_size += (cur_lines > min_lines) ? 
				  cur_lines - min_lines : 0;

	sc_vtb_destroy(history);
	free(history, M_DEVBUF);
}
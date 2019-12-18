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
typedef  int /*<<< orphan*/  sc_vtb_t ;

/* Variables and functions */
 int imin (int,int) ; 
 int /*<<< orphan*/  sc_vtb_append (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int sc_vtb_cols (int /*<<< orphan*/ *) ; 
 int sc_vtb_pos (int /*<<< orphan*/ *,int,int) ; 
 int sc_vtb_rows (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sc_vtb_seek (int /*<<< orphan*/ *,int) ; 
 int sc_vtb_tail (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
copy_history(sc_vtb_t *from, sc_vtb_t *to)
{
	int lines;
	int cols;
	int cols1;
	int cols2;
	int pos;
	int i;

	lines = sc_vtb_rows(from);
	cols1 = sc_vtb_cols(from);
	cols2 = sc_vtb_cols(to);
	cols = imin(cols1, cols2);
	pos = sc_vtb_tail(from);
	for (i = 0; i < lines; ++i) {
		sc_vtb_append(from, pos, to, cols);
		if (cols < cols2)
			sc_vtb_seek(to, sc_vtb_pos(to, 
						   sc_vtb_tail(to), 
						   cols2 - cols));
		pos = sc_vtb_pos(from, pos, cols1);
	}
}
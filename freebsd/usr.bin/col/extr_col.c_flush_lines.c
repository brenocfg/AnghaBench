#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * l_prev; scalar_t__ l_line; struct TYPE_5__* l_next; } ;
typedef  TYPE_1__ LINE ;

/* Variables and functions */
 int /*<<< orphan*/  flush_blanks () ; 
 int /*<<< orphan*/  flush_line (TYPE_1__*) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  free_line (TYPE_1__*) ; 
 TYPE_1__* lines ; 
 int /*<<< orphan*/  nblank_lines ; 

__attribute__((used)) static void
flush_lines(int nflush)
{
	LINE *l;

	while (--nflush >= 0) {
		l = lines;
		lines = l->l_next;
		if (l->l_line) {
			flush_blanks();
			flush_line(l);
		}
		if (l->l_line || l->l_next)
			nblank_lines++;
		if (l->l_line)
			(void)free(l->l_line);
		free_line(l);
	}
	if (lines)
		lines->l_prev = NULL;
}
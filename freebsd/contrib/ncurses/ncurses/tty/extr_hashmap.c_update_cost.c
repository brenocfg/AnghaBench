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
typedef  int /*<<< orphan*/  SCREEN ;
typedef  int /*<<< orphan*/  NCURSES_CH_T ;

/* Variables and functions */
 int /*<<< orphan*/  CharEq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TEXTWIDTH (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
update_cost(SCREEN *sp, NCURSES_CH_T * from, NCURSES_CH_T * to)
{
    int cost = 0;
    int i;

    for (i = TEXTWIDTH(sp); i > 0; i--, from++, to++)
	if (!(CharEq(*from, *to)))
	    cost++;

    return cost;
}
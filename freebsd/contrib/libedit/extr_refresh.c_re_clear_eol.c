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
typedef  int /*<<< orphan*/  EditLine ;

/* Variables and functions */
 int /*<<< orphan*/  ELRE_DEBUG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __F ; 
 int /*<<< orphan*/  terminal_clear_EOL (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
re_clear_eol(EditLine *el, int fx, int sx, int diff)
{

	ELRE_DEBUG(1, (__F, "re_clear_eol sx %d, fx %d, diff %d\n",
	    sx, fx, diff));

	if (fx < 0)
		fx = -fx;
	if (sx < 0)
		sx = -sx;
	if (fx > diff)
		diff = fx;
	if (sx > diff)
		diff = sx;

	ELRE_DEBUG(1, (__F, "re_clear_eol %d\n", diff));
	terminal_clear_EOL(el, diff);
}
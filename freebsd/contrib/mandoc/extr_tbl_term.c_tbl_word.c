#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct termp {int fonti; } ;
struct tbl_dat {int /*<<< orphan*/  string; TYPE_1__* layout; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int TBL_CELL_BOLD ; 
 int TBL_CELL_ITALIC ; 
 int /*<<< orphan*/  TERMFONT_BOLD ; 
 int /*<<< orphan*/  TERMFONT_UNDER ; 
 int /*<<< orphan*/  term_fontpopq (struct termp*,int) ; 
 int /*<<< orphan*/  term_fontpush (struct termp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  term_word (struct termp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tbl_word(struct termp *tp, const struct tbl_dat *dp)
{
	int		 prev_font;

	prev_font = tp->fonti;
	if (dp->layout->flags & TBL_CELL_BOLD)
		term_fontpush(tp, TERMFONT_BOLD);
	else if (dp->layout->flags & TBL_CELL_ITALIC)
		term_fontpush(tp, TERMFONT_UNDER);

	term_word(tp, dp->string);

	term_fontpopq(tp, prev_font);
}
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
typedef  int /*<<< orphan*/  TEXTH ;
typedef  int /*<<< orphan*/  TEXT ;

/* Variables and functions */
 int /*<<< orphan*/ * TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q ; 
 int /*<<< orphan*/  text_free (int /*<<< orphan*/ *) ; 

void
text_lfree(TEXTH *headp)
{
	TEXT *tp;

	while ((tp = TAILQ_FIRST(headp)) != NULL) {
		TAILQ_REMOVE(headp, tp, q);
		text_free(tp);
	}
}
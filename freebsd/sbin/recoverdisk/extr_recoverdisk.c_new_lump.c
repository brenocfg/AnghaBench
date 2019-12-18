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
struct lump {int state; void* len; void* start; } ;
typedef  void* off_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct lump*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  list ; 
 int /*<<< orphan*/  lumps ; 
 struct lump* malloc (int) ; 

__attribute__((used)) static void
new_lump(off_t start, off_t len, int state)
{
	struct lump *lp;

	lp = malloc(sizeof *lp);
	if (lp == NULL)
		err(1, "Malloc failed");
	lp->start = start;
	lp->len = len;
	lp->state = state;
	TAILQ_INSERT_TAIL(&lumps, lp, list);
}
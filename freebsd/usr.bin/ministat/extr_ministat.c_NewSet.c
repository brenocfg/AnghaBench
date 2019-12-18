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
struct dataset {int lpoints; int /*<<< orphan*/  syy; int /*<<< orphan*/ * points; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAN ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 void* calloc (int,int) ; 

__attribute__((used)) static struct dataset *
NewSet(void)
{
	struct dataset *ds;

	ds = calloc(1, sizeof *ds);
	assert(ds != NULL);
	ds->lpoints = 100000;
	ds->points = calloc(sizeof *ds->points, ds->lpoints);
	assert(ds->points != NULL);
	ds->syy = NAN;
	return(ds);
}
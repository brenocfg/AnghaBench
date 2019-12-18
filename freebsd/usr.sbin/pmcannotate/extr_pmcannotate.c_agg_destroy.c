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
struct aggent {struct aggent* ag_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct aggent*) ; 

__attribute__((used)) static void
agg_destroy(struct aggent *agg)
{

	free(agg->ag_name);
	free(agg);
}
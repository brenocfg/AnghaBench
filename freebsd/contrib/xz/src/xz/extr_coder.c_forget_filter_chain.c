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
struct TYPE_2__ {int /*<<< orphan*/ * options; } ;

/* Variables and functions */
 TYPE_1__* filters ; 
 size_t filters_count ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
forget_filter_chain(void)
{
	// Setting a preset makes us forget a possibly defined custom
	// filter chain.
	while (filters_count > 0) {
		--filters_count;
		free(filters[filters_count].options);
		filters[filters_count].options = NULL;
	}

	return;
}
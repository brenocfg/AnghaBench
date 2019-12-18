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
struct autofs_node {int an_cached; } ;

/* Variables and functions */

__attribute__((used)) static void
autofs_cache_callout(void *context)
{
	struct autofs_node *anp;

	anp = context;
	anp->an_cached = false;
}
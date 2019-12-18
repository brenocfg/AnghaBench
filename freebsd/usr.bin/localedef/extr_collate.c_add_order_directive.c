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
struct TYPE_2__ {scalar_t__ directive_count; } ;

/* Variables and functions */
 scalar_t__ COLL_WEIGHTS_MAX ; 
 TYPE_1__ collinfo ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 

void
add_order_directive(void)
{
	if (collinfo.directive_count >= COLL_WEIGHTS_MAX) {
		fprintf(stderr,"too many directives (max %d)", COLL_WEIGHTS_MAX);
	}
	collinfo.directive_count++;
}
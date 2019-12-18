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
struct _citrus_mapper {scalar_t__ cm_closure; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 

__attribute__((used)) static void
/*ARGSUSED*/
_citrus_mapper_646_mapper_uninit(struct _citrus_mapper *cm)
{

	if (cm && cm->cm_closure)
		free(cm->cm_closure);
}
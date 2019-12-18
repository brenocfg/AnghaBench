#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* res_state ;
struct TYPE_6__ {int /*<<< orphan*/ * ext; } ;
struct TYPE_7__ {TYPE_1__ _ext; } ;
struct TYPE_8__ {TYPE_2__ _u; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  res_ndestroy (TYPE_3__*) ; 

__attribute__((used)) static void
free_res(void *ptr)
{
	res_state statp = ptr;

	if (statp->_u._ext.ext != NULL)
		res_ndestroy(statp);
	free(statp);
}
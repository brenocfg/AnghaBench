#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  union ccb {int dummy; } ccb ;
struct cam_periph {TYPE_2__* path; int /*<<< orphan*/  periph_allocated; } ;
struct TYPE_4__ {TYPE_1__* device; } ;
struct TYPE_3__ {int /*<<< orphan*/  ccbq; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_CAMCCB ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  cam_ccbq_take_opening (int /*<<< orphan*/ *) ; 
 union ccb* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static union ccb *
xpt_get_ccb_nowait(struct cam_periph *periph)
{
	union ccb *new_ccb;

	new_ccb = malloc(sizeof(*new_ccb), M_CAMCCB, M_ZERO|M_NOWAIT);
	if (new_ccb == NULL)
		return (NULL);
	periph->periph_allocated++;
	cam_ccbq_take_opening(&periph->path->device->ccbq);
	return (new_ccb);
}
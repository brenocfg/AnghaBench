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
struct cam_ccbq {int total_openings; int dev_openings; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (struct cam_ccbq*,int) ; 
 scalar_t__ camq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int fls (int) ; 
 int /*<<< orphan*/  imax (int,int) ; 

int
cam_ccbq_init(struct cam_ccbq *ccbq, int openings)
{
	bzero(ccbq, sizeof(*ccbq));
	if (camq_init(&ccbq->queue,
	    imax(64, 1 << fls(openings + openings / 2))) != 0)
		return (1);
	ccbq->total_openings = openings;
	ccbq->dev_openings = openings;
	return (0);
}
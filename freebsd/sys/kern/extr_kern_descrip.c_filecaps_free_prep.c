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
typedef  int /*<<< orphan*/  u_long ;
struct filecaps {int /*<<< orphan*/ * fc_ioctls; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (struct filecaps*,int) ; 

__attribute__((used)) static u_long *
filecaps_free_prep(struct filecaps *fcaps)
{
	u_long *ioctls;

	ioctls = fcaps->fc_ioctls;
	bzero(fcaps, sizeof(*fcaps));
	return (ioctls);
}
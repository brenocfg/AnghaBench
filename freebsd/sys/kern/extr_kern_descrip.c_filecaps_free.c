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
struct filecaps {int /*<<< orphan*/  fc_ioctls; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_FILECAPS ; 
 int /*<<< orphan*/  bzero (struct filecaps*,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
filecaps_free(struct filecaps *fcaps)
{

	free(fcaps->fc_ioctls, M_FILECAPS);
	bzero(fcaps, sizeof(*fcaps));
}
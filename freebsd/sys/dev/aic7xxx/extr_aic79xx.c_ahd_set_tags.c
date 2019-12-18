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
struct ahd_softc {int dummy; } ;
struct ahd_devinfo {int /*<<< orphan*/  lun; int /*<<< orphan*/  target; int /*<<< orphan*/  channel; } ;
typedef  int /*<<< orphan*/  ahd_queue_alg ;

/* Variables and functions */
 int /*<<< orphan*/  AC_TRANSFER_NEG ; 
 int /*<<< orphan*/  ahd_platform_set_tags (struct ahd_softc*,struct ahd_devinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_send_async (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
ahd_set_tags(struct ahd_softc *ahd, struct ahd_devinfo *devinfo,
	     ahd_queue_alg alg)
{
	ahd_platform_set_tags(ahd, devinfo, alg);
	ahd_send_async(ahd, devinfo->channel, devinfo->target,
		       devinfo->lun, AC_TRANSFER_NEG, &alg);
}
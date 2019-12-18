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
struct ahc_softc {int dummy; } ;
struct ahc_devinfo {int channel; int target; int lun; } ;

/* Variables and functions */
 char* ahc_name (struct ahc_softc*) ; 
 int /*<<< orphan*/  printf (char*,char*,int,int,int) ; 

void
ahc_print_devinfo(struct ahc_softc *ahc, struct ahc_devinfo *devinfo)
{
	printf("%s:%c:%d:%d: ", ahc_name(ahc), devinfo->channel,
	       devinfo->target, devinfo->lun);
}
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
struct ahc_softc {int dummy; } ;
struct TYPE_2__ {char* errmesg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_CHANNELS ; 
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 int /*<<< orphan*/  CAM_NO_HBA ; 
 int /*<<< orphan*/  CAM_TARGET_WILDCARD ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ROLE_UNKNOWN ; 
 int /*<<< orphan*/  SCB_LIST_NULL ; 
 int /*<<< orphan*/  SEQADDR0 ; 
 int /*<<< orphan*/  SEQADDR1 ; 
 int /*<<< orphan*/  ahc_abort_scbs (struct ahc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_dump_card_state (struct ahc_softc*) ; 
 TYPE_1__* ahc_hard_errors ; 
 int ahc_inb (struct ahc_softc*,int /*<<< orphan*/ ) ; 
 char* ahc_name (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_shutdown (struct ahc_softc*) ; 
 int num_errors ; 
 int /*<<< orphan*/  printf (char*,char*,char*,int) ; 

void
ahc_handle_brkadrint(struct ahc_softc *ahc)
{
	/*
	 * We upset the sequencer :-(
	 * Lookup the error message
	 */
	int i;
	int error;

	error = ahc_inb(ahc, ERROR);
	for (i = 0; error != 1 && i < num_errors; i++)
		error >>= 1;
	printf("%s: brkadrint, %s at seqaddr = 0x%x\n",
	       ahc_name(ahc), ahc_hard_errors[i].errmesg,
	       ahc_inb(ahc, SEQADDR0) |
	       (ahc_inb(ahc, SEQADDR1) << 8));

	ahc_dump_card_state(ahc);

	/* Tell everyone that this HBA is no longer available */
	ahc_abort_scbs(ahc, CAM_TARGET_WILDCARD, ALL_CHANNELS,
		       CAM_LUN_WILDCARD, SCB_LIST_NULL, ROLE_UNKNOWN,
		       CAM_NO_HBA);

	/* Disable all interrupt sources by resetting the controller */
	ahc_shutdown(ahc);
}
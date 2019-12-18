#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
typedef  TYPE_1__* hcb_p ;
struct TYPE_4__ {int scsi_mode; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int INB (int /*<<< orphan*/ ) ; 
 int SMODE ; 
 int /*<<< orphan*/  nc_stest4 ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/  sym_init (TYPE_1__*,int) ; 
 char* sym_scsi_bus_mode (int) ; 
 int /*<<< orphan*/  xpt_print_path (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sym_int_sbmc (hcb_p np)
{
	u_char scsi_mode = INB (nc_stest4) & SMODE;

	/*
	 *  Notify user.
	 */
	xpt_print_path(np->path);
	printf("SCSI BUS mode change from %s to %s.\n",
		sym_scsi_bus_mode(np->scsi_mode), sym_scsi_bus_mode(scsi_mode));

	/*
	 *  Should suspend command processing for a few seconds and
	 *  reinitialize all except the chip.
	 */
	sym_init (np, 2);
}
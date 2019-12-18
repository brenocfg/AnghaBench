#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINTN ;
struct TYPE_9__ {TYPE_2__* ConOut; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* QueryMode ) (TYPE_2__*,int,scalar_t__*,scalar_t__*) ;TYPE_1__* Mode; int /*<<< orphan*/  (* SetMode ) (TYPE_2__*,unsigned int) ;} ;
struct TYPE_7__ {int Mode; int MaxMode; } ;
typedef  TYPE_2__ SIMPLE_TEXT_OUTPUT_INTERFACE ;
typedef  int /*<<< orphan*/  EFI_STATUS ;

/* Variables and functions */
 int CMD_ERROR ; 
 int CMD_OK ; 
 scalar_t__ EFI_ERROR (int /*<<< orphan*/ ) ; 
 TYPE_6__* ST ; 
 int /*<<< orphan*/  efi_cons_update_mode () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 unsigned int strtol (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,unsigned int,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,int,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static int
command_mode(int argc, char *argv[])
{
	UINTN cols, rows;
	unsigned int mode;
	int i;
	char *cp;
	EFI_STATUS status;
	SIMPLE_TEXT_OUTPUT_INTERFACE *conout;

	conout = ST->ConOut;

	if (argc > 1) {
		mode = strtol(argv[1], &cp, 0);
		if (cp[0] != '\0') {
			printf("Invalid mode\n");
			return (CMD_ERROR);
		}
		status = conout->QueryMode(conout, mode, &cols, &rows);
		if (EFI_ERROR(status)) {
			printf("invalid mode %d\n", mode);
			return (CMD_ERROR);
		}
		status = conout->SetMode(conout, mode);
		if (EFI_ERROR(status)) {
			printf("couldn't set mode %d\n", mode);
			return (CMD_ERROR);
		}
		(void) efi_cons_update_mode();
		return (CMD_OK);
	}

	printf("Current mode: %d\n", conout->Mode->Mode);
	for (i = 0; i <= conout->Mode->MaxMode; i++) {
		status = conout->QueryMode(conout, i, &cols, &rows);
		if (EFI_ERROR(status))
			continue;
		printf("Mode %d: %u columns, %u rows\n", i, (unsigned)cols,
		    (unsigned)rows);
	}

	if (i != 0)
		printf("Select a mode with the command \"mode <number>\"\n");

	return (CMD_OK);
}
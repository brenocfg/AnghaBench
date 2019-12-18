#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ (* OpenProtocol ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  ConsoleInHandle; int /*<<< orphan*/ * ConIn; TYPE_1__* ConOut; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* EnableCursor ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
typedef  scalar_t__ EFI_STATUS ;

/* Variables and functions */
 TYPE_4__* BS ; 
 int /*<<< orphan*/  EFI_OPEN_PROTOCOL_GET_PROTOCOL ; 
 scalar_t__ EFI_SUCCESS ; 
 int /*<<< orphan*/  IH ; 
 TYPE_3__* ST ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * conin ; 
 int /*<<< orphan*/ * coninex ; 
 TYPE_1__* conout ; 
 scalar_t__ efi_cons_update_mode () ; 
 int /*<<< orphan*/  simple_input_ex_guid ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
efi_cons_init(int arg)
{
	EFI_STATUS status;

	if (conin != NULL)
		return (0);

	conout = ST->ConOut;
	conin = ST->ConIn;

	conout->EnableCursor(conout, TRUE);
	status = BS->OpenProtocol(ST->ConsoleInHandle, &simple_input_ex_guid,
	    (void **)&coninex, IH, NULL, EFI_OPEN_PROTOCOL_GET_PROTOCOL);
	if (status != EFI_SUCCESS)
		coninex = NULL;

	if (efi_cons_update_mode())
		return (0);

	return (1);
}
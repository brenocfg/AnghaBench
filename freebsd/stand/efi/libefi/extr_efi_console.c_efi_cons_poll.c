#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ (* CheckEvent ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {int /*<<< orphan*/ * WaitForKey; } ;
struct TYPE_4__ {int /*<<< orphan*/ * WaitForKeyEx; } ;
typedef  scalar_t__ EFI_STATUS ;

/* Variables and functions */
 TYPE_3__* BS ; 
 scalar_t__ EFI_SUCCESS ; 
 TYPE_2__* conin ; 
 TYPE_1__* coninex ; 
 int efi_readkey () ; 
 int efi_readkey_ex () ; 
 int key_pending ; 
 scalar_t__ keybuf_ischar () ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ *) ; 

int
efi_cons_poll(void)
{
	EFI_STATUS status;

	if (keybuf_ischar() || key_pending)
		return (1);

	/*
	 * Some EFI implementation (u-boot for example) do not support
	 * WaitForKey().
	 * CheckEvent() can clear the signaled state.
	 */
	if (coninex != NULL) {
		if (coninex->WaitForKeyEx == NULL) {
			key_pending = efi_readkey_ex();
		} else {
			status = BS->CheckEvent(coninex->WaitForKeyEx);
			key_pending = status == EFI_SUCCESS;
		}
	} else {
		if (conin->WaitForKey == NULL) {
			key_pending = efi_readkey();
		} else {
			status = BS->CheckEvent(conin->WaitForKey);
			key_pending = status == EFI_SUCCESS;
		}
	}

	return (key_pending);
}
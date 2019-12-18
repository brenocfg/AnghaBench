#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_11__ {scalar_t__ (* ReadKeyStrokeEx ) (TYPE_4__*,TYPE_2__*) ;} ;
struct TYPE_10__ {char UnicodeChar; } ;
struct TYPE_8__ {int KeyShiftState; } ;
struct TYPE_9__ {TYPE_3__ Key; TYPE_1__ KeyState; } ;
typedef  scalar_t__ EFI_STATUS ;
typedef  TYPE_2__ EFI_KEY_DATA ;
typedef  TYPE_3__ EFI_INPUT_KEY ;

/* Variables and functions */
 int EFI_LEFT_CONTROL_PRESSED ; 
 int EFI_RIGHT_CONTROL_PRESSED ; 
 int EFI_SHIFT_STATE_VALID ; 
 scalar_t__ EFI_SUCCESS ; 
 TYPE_4__* coninex ; 
 int /*<<< orphan*/  keybuf_inschar (TYPE_3__*) ; 
 scalar_t__ stub1 (TYPE_4__*,TYPE_2__*) ; 

__attribute__((used)) static bool
efi_readkey_ex(void)
{
	EFI_STATUS status;
	EFI_INPUT_KEY *kp;
	EFI_KEY_DATA  key_data;
	uint32_t kss;

	status = coninex->ReadKeyStrokeEx(coninex, &key_data);
	if (status == EFI_SUCCESS) {
		kss = key_data.KeyState.KeyShiftState;
		kp = &key_data.Key;
		if (kss & EFI_SHIFT_STATE_VALID) {

			/*
			 * quick mapping to control chars, replace with
			 * map lookup later.
			 */
			if (kss & EFI_RIGHT_CONTROL_PRESSED ||
			    kss & EFI_LEFT_CONTROL_PRESSED) {
				if (kp->UnicodeChar >= 'a' &&
				    kp->UnicodeChar <= 'z') {
					kp->UnicodeChar -= 'a';
					kp->UnicodeChar++;
				}
			}
		}

		keybuf_inschar(kp);
		return (true);
	}
	return (false);
}
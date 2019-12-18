#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ (* ReadKeyStroke ) (TYPE_1__*,int /*<<< orphan*/ *) ;} ;
typedef  scalar_t__ EFI_STATUS ;
typedef  int /*<<< orphan*/  EFI_INPUT_KEY ;

/* Variables and functions */
 scalar_t__ EFI_SUCCESS ; 
 TYPE_1__* conin ; 
 int /*<<< orphan*/  keybuf_inschar (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
efi_readkey(void)
{
	EFI_STATUS status;
	EFI_INPUT_KEY key;

	status = conin->ReadKeyStroke(conin, &key);
	if (status == EFI_SUCCESS) {
		keybuf_inschar(&key);
		return (true);
	}
	return (false);
}
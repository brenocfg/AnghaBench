#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct image_params {TYPE_1__* args; scalar_t__ image_header; } ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_4__ {int /*<<< orphan*/  e_flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  fname; } ;
typedef  TYPE_2__ Elf_Ehdr ;

/* Variables and functions */
 scalar_t__ EF_ARM_EABI_FREEBSD_MIN ; 
 scalar_t__ EF_ARM_EABI_VERSION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  uprintf (char*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
elf32_arm_abi_supported(struct image_params *imgp)
{
	const Elf_Ehdr *hdr = (const Elf_Ehdr *)imgp->image_header;

	/*
	 * When configured for EABI, FreeBSD supports EABI vesions 4 and 5.
	 */
	if (EF_ARM_EABI_VERSION(hdr->e_flags) < EF_ARM_EABI_FREEBSD_MIN) {
		if (bootverbose)
			uprintf("Attempting to execute non EABI binary (rev %d) image %s",
			    EF_ARM_EABI_VERSION(hdr->e_flags), imgp->args->fname);
		return (FALSE);
	}
	return (TRUE);
}
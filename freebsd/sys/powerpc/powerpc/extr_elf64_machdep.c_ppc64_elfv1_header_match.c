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
struct image_params {scalar_t__ image_header; } ;
typedef  int boolean_t ;
struct TYPE_2__ {int e_flags; } ;
typedef  TYPE_1__ Elf64_Ehdr ;

/* Variables and functions */

__attribute__((used)) static boolean_t
ppc64_elfv1_header_match(struct image_params *params)
{
	const Elf64_Ehdr *hdr = (const Elf64_Ehdr *)params->image_header;
	int abi = (hdr->e_flags & 3);

	return (abi == 0 || abi == 1);
}
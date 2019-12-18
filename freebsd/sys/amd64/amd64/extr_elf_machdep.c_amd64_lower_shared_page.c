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
struct sysentvec {int /*<<< orphan*/  sv_psstrings; int /*<<< orphan*/  sv_usrstack; int /*<<< orphan*/  sv_shared_page_base; int /*<<< orphan*/  sv_maxuser; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ hw_lower_amd64_sharedpage ; 

void
amd64_lower_shared_page(struct sysentvec *sv)
{
	if (hw_lower_amd64_sharedpage != 0) {
		sv->sv_maxuser -= PAGE_SIZE;
		sv->sv_shared_page_base -= PAGE_SIZE;
		sv->sv_usrstack -= PAGE_SIZE;
		sv->sv_psstrings -= PAGE_SIZE;
	}
}
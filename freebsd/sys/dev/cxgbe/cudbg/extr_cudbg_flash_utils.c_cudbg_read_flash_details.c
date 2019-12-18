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
struct cudbg_flash_hdr {int dummy; } ;

/* Variables and functions */
 int cudbg_read_flash (void*,void*,int,int /*<<< orphan*/ ) ; 

int cudbg_read_flash_details(void *handle, struct cudbg_flash_hdr *data)
{
	int rc;
	rc = cudbg_read_flash(handle, (void *)data,
			      sizeof(struct cudbg_flash_hdr), 0);

	return rc;
}
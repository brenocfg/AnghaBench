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

/* Variables and functions */
 int /*<<< orphan*/  M_OSD ; 
 int /*<<< orphan*/  OSD_DEBUG (char*) ; 
 int /*<<< orphan*/  free (void**,int /*<<< orphan*/ ) ; 

void
osd_free_reserved(void **rsv)
{

	OSD_DEBUG("Discarding reserved slot array.");
	free(rsv, M_OSD);
}
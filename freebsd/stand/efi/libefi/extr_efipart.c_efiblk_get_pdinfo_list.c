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
struct devsw {scalar_t__ dv_type; } ;
typedef  int /*<<< orphan*/  pdinfo_list_t ;

/* Variables and functions */
 scalar_t__ DEVT_CD ; 
 scalar_t__ DEVT_DISK ; 
 scalar_t__ DEVT_FD ; 
 int /*<<< orphan*/  cdinfo ; 
 int /*<<< orphan*/  fdinfo ; 
 int /*<<< orphan*/  hdinfo ; 

pdinfo_list_t *
efiblk_get_pdinfo_list(struct devsw *dev)
{
	if (dev->dv_type == DEVT_DISK)
		return (&hdinfo);
	if (dev->dv_type == DEVT_CD)
		return (&cdinfo);
	if (dev->dv_type == DEVT_FD)
		return (&fdinfo);
	return (NULL);
}
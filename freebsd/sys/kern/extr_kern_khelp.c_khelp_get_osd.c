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
struct osd {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  OSD_KHELP ; 
 void* osd_get (int /*<<< orphan*/ ,struct osd*,int /*<<< orphan*/ ) ; 

void *
khelp_get_osd(struct osd *hosd, int32_t id)
{

	return (osd_get(OSD_KHELP, hosd, id));
}
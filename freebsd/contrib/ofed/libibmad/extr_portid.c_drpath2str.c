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
struct TYPE_3__ {int drslid; int drdlid; int* p; int cnt; } ;
typedef  TYPE_1__ ib_dr_path_t ;

/* Variables and functions */
 int snprintf (char*,size_t,char*,int,...) ; 

char *drpath2str(ib_dr_path_t * path, char *dstr, size_t dstr_size)
{
	int i = 0;
	int rc = snprintf(dstr, dstr_size, "slid %u; dlid %u; %d",
			  path->drslid, path->drdlid, path->p[0]);
	if (rc >= (int)dstr_size)
		return dstr;
	for (i = 1; i <= path->cnt; i++) {
		rc += snprintf(dstr + rc, dstr_size - rc, ",%d", path->p[i]);
		if (rc >= (int)dstr_size)
			break;
	}
	return (dstr);
}
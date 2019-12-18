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
struct loadavg {double fscale; scalar_t__* ldavg; } ;
typedef  int /*<<< orphan*/  loadinfo ;
typedef  int /*<<< orphan*/  fixpt_t ;

/* Variables and functions */
 int CTL_VM ; 
 int MIN (int,int) ; 
 int VM_LOADAVG ; 
 scalar_t__ sysctl (int*,int,struct loadavg*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
getloadavg(double loadavg[], int nelem)
{
	struct loadavg loadinfo;
	int i, mib[2];
	size_t size;

	mib[0] = CTL_VM;
	mib[1] = VM_LOADAVG;
	size = sizeof(loadinfo);
	if (sysctl(mib, 2, &loadinfo, &size, NULL, 0) < 0)
		return (-1);

	nelem = MIN(nelem, sizeof(loadinfo.ldavg) / sizeof(fixpt_t));
	for (i = 0; i < nelem; i++)
		loadavg[i] = (double) loadinfo.ldavg[i] / loadinfo.fscale;
	return (nelem);
}
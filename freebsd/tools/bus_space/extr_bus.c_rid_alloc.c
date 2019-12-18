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
struct resource {int dummy; } ;
struct TYPE_3__ {int fd; } ;

/* Variables and functions */
 int INT_MAX ; 
 int nrids ; 
 void* realloc (TYPE_1__*,int) ; 
 TYPE_1__* ridtbl ; 

__attribute__((used)) static int
rid_alloc(void)
{
	void *newtbl;
	int rid;

	for (rid = 0; rid < nrids; rid++) {
		if (ridtbl[rid].fd == -1)
			break;
	}
	if (rid == nrids) {
		nrids++;
		newtbl = realloc(ridtbl, sizeof(struct resource) * nrids);
		if (newtbl == NULL) {
			nrids--;
			return (-1);
		} else
			ridtbl = newtbl;
	}
	ridtbl[rid].fd = INT_MAX;
	return (rid);
}
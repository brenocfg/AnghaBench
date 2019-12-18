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
struct nlist {int dummy; } ;
struct TYPE_3__ {int (* fn ) (int,struct nlist*) ;} ;

/* Variables and functions */
 unsigned int nitems (TYPE_1__*) ; 
 TYPE_1__* nlist_fn ; 
 int stub1 (int,struct nlist*) ; 

int
__fdnlist(int fd, struct nlist *list)
{
	int n = -1;
	unsigned int i;

	for (i = 0; i < nitems(nlist_fn); i++) {
		n = (nlist_fn[i].fn)(fd, list);
		if (n != -1)
			break;
	}
	return (n);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* sockets; } ;
typedef  TYPE_1__ ifconfig_handle_t ;

/* Variables and functions */
 int AF_MAX ; 
 TYPE_1__* calloc (int,int) ; 

ifconfig_handle_t *
ifconfig_open(void)
{
	ifconfig_handle_t *h;

	h = calloc(1, sizeof(*h));

	if (h == NULL) {
		return (NULL);
	}
	for (int i = 0; i <= AF_MAX; i++) {
		h->sockets[i] = -1;
	}

	return (h);
}
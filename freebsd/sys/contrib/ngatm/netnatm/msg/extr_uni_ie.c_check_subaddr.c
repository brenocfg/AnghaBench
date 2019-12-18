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
struct uni_subaddr {int type; int len; } ;

/* Variables and functions */
#define  UNI_SUBADDR_ATME 129 
#define  UNI_SUBADDR_NSAP 128 

__attribute__((used)) static int
check_subaddr(struct uni_subaddr *addr)
{
	switch(addr->type) {
	  default:
		return -1;

	  case UNI_SUBADDR_NSAP:
		if(addr->len != 20)
			return -1;
		break;

	  case UNI_SUBADDR_ATME:
		if(addr->len > 20)
			return -1;
		break;
	}
	return 0;
}
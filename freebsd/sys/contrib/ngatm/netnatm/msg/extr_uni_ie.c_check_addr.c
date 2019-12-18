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
typedef  size_t u_int ;
struct uni_addr {int plan; int len; int* addr; int /*<<< orphan*/  type; } ;

/* Variables and functions */
#define  UNI_ADDR_ATME 129 
#define  UNI_ADDR_E164 128 
 int /*<<< orphan*/  UNI_ADDR_INTERNATIONAL ; 
 int /*<<< orphan*/  UNI_ADDR_UNKNOWN ; 

__attribute__((used)) static int
check_addr(struct uni_addr *addr)
{
	u_int i;

	switch(addr->plan) {
	  default:
		return -1;

	  case UNI_ADDR_E164:
		if(addr->type != UNI_ADDR_INTERNATIONAL)
			return -1;
		if(addr->len > 15 || addr->len == 0)
			return -1;
		for(i = 0; i < addr->len; i++)
			if(addr->addr[i] == 0 || (addr->addr[i] & 0x80))
				return -1;
		break;

	  case UNI_ADDR_ATME:
		if(addr->type != UNI_ADDR_UNKNOWN)
			return -1;
		if(addr->len != 20)
			return -1;
		break;
	}

	return 0;
}
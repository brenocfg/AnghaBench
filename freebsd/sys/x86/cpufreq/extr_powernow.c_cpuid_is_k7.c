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
typedef  int u_int ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 

__attribute__((used)) static int
cpuid_is_k7(u_int cpuid)
{

	switch (cpuid) {
	case 0x760:
	case 0x761:
	case 0x762:
	case 0x770:
	case 0x771:
	case 0x780:
	case 0x781:
	case 0x7a0:
		return (TRUE);
	}
	return (FALSE);
}
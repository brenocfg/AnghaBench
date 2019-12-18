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
typedef  int /*<<< orphan*/  printfcn ;

/* Variables and functions */
#define  IFT_ETHER 130 
#define  IFT_ISO88023 129 
#define  IFT_STARLAN 128 
 int /*<<< orphan*/  print_1650 ; 

__attribute__((used)) static printfcn
findlink(int type)
{
	switch(type) {
	case IFT_ETHER:
	case IFT_ISO88023:
	case IFT_STARLAN:
		return print_1650;
	}

	return 0;
}
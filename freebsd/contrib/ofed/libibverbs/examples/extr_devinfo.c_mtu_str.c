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
typedef  enum ibv_mtu { ____Placeholder_ibv_mtu } ibv_mtu ;

/* Variables and functions */
#define  IBV_MTU_1024 132 
#define  IBV_MTU_2048 131 
#define  IBV_MTU_256 130 
#define  IBV_MTU_4096 129 
#define  IBV_MTU_512 128 

__attribute__((used)) static const char *mtu_str(enum ibv_mtu max_mtu)
{
	switch (max_mtu) {
	case IBV_MTU_256:  return "256";
	case IBV_MTU_512:  return "512";
	case IBV_MTU_1024: return "1024";
	case IBV_MTU_2048: return "2048";
	case IBV_MTU_4096: return "4096";
	default:           return "invalid MTU";
	}
}
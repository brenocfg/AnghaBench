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
typedef  int /*<<< orphan*/  u32 ;
struct ath79_eth_pll_data {int /*<<< orphan*/  pll_1000; int /*<<< orphan*/  pll_100; int /*<<< orphan*/  pll_10; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  SPEED_10 130 
#define  SPEED_100 129 
#define  SPEED_1000 128 
 struct ath79_eth_pll_data ath79_eth0_pll_data ; 
 struct ath79_eth_pll_data ath79_eth1_pll_data ; 

__attribute__((used)) static u32 ath79_get_eth_pll(unsigned int mac, int speed)
{
	struct ath79_eth_pll_data *pll_data;
	u32 pll_val;

	switch (mac) {
	case 0:
		pll_data = &ath79_eth0_pll_data;
		break;
	case 1:
		pll_data = &ath79_eth1_pll_data;
		break;
	default:
		BUG();
	}

	switch (speed) {
	case SPEED_10:
		pll_val = pll_data->pll_10;
		break;
	case SPEED_100:
		pll_val = pll_data->pll_100;
		break;
	case SPEED_1000:
		pll_val = pll_data->pll_1000;
		break;
	default:
		BUG();
	}

	return pll_val;
}
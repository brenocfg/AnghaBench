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
struct al_eth_kr_coef_up_data {int c_minus; int c_plus; int c_zero; } ;
typedef  enum al_eth_kr_coef { ____Placeholder_al_eth_kr_coef } al_eth_kr_coef ;
typedef  enum al_eth_kr_cl72_coef_op { ____Placeholder_al_eth_kr_cl72_coef_op } al_eth_kr_cl72_coef_op ;

/* Variables and functions */
#define  AL_ETH_KR_COEF_C_MINUS 130 
#define  AL_ETH_KR_COEF_C_PLUS 129 
#define  AL_ETH_KR_COEF_C_ZERO 128 

__attribute__((used)) static void
al_eth_kr_lt_coef_set(struct al_eth_kr_coef_up_data *ldcoeff,
    enum al_eth_kr_coef coef, enum al_eth_kr_cl72_coef_op op)
{

	switch (coef) {
	case AL_ETH_KR_COEF_C_MINUS:
		ldcoeff->c_minus = op;
		break;
	case AL_ETH_KR_COEF_C_PLUS:
		ldcoeff->c_plus = op;
		break;
	case AL_ETH_KR_COEF_C_ZERO:
		ldcoeff->c_zero = op;
		break;
	}
}
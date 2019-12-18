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
struct al_eth_kr_coef_up_data {int dummy; } ;
struct al_eth_kr_data {struct al_eth_kr_coef_up_data last_lpcoeff; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ al_memcmp (struct al_eth_kr_coef_up_data*,struct al_eth_kr_coef_up_data*,int) ; 
 int /*<<< orphan*/  al_memcpy (struct al_eth_kr_coef_up_data*,struct al_eth_kr_coef_up_data*,int) ; 

__attribute__((used)) static boolean_t
al_eth_lp_coeff_up_change(struct al_eth_kr_data *kr_data,
    struct al_eth_kr_coef_up_data *lpcoeff)
{
	struct al_eth_kr_coef_up_data *last_lpcoeff = &kr_data->last_lpcoeff;

	if (al_memcmp(last_lpcoeff, lpcoeff,
	    sizeof(struct al_eth_kr_coef_up_data)) == 0) {
		return (FALSE);
	}

	al_memcpy(last_lpcoeff, lpcoeff, sizeof(struct al_eth_kr_coef_up_data));

	return (TRUE);
}
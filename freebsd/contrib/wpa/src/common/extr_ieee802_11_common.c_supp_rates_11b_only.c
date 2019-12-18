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
struct ieee802_11_elems {int supp_rates_len; int ext_supp_rates_len; int /*<<< orphan*/ * ext_supp_rates; int /*<<< orphan*/ * supp_rates; } ;

/* Variables and functions */
 scalar_t__ is_11b (int /*<<< orphan*/ ) ; 

int supp_rates_11b_only(struct ieee802_11_elems *elems)
{
	int num_11b = 0, num_others = 0;
	int i;

	if (elems->supp_rates == NULL && elems->ext_supp_rates == NULL)
		return 0;

	for (i = 0; elems->supp_rates && i < elems->supp_rates_len; i++) {
		if (is_11b(elems->supp_rates[i]))
			num_11b++;
		else
			num_others++;
	}

	for (i = 0; elems->ext_supp_rates && i < elems->ext_supp_rates_len;
	     i++) {
		if (is_11b(elems->ext_supp_rates[i]))
			num_11b++;
		else
			num_others++;
	}

	return num_11b > 0 && num_others == 0;
}
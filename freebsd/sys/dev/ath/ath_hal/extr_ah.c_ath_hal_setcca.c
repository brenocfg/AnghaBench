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
struct ath_hal {int dummy; } ;

/* Variables and functions */

void
ath_hal_setcca(struct ath_hal *ah, int ena)
{
	/*
	 * NB: fill me in; this is not provided by default because disabling
	 *     CCA in most locales violates regulatory.
	 */
}
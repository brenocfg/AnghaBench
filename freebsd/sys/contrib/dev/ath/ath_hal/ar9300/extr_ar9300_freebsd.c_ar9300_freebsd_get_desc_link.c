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
typedef  int /*<<< orphan*/  uint32_t ;
struct ath_hal {int dummy; } ;
struct ar9300_txc {int /*<<< orphan*/  ds_link; } ;

/* Variables and functions */
 struct ar9300_txc* AR9300TXC (void*) ; 

void
ar9300_freebsd_get_desc_link(struct ath_hal *ah, void *ds, uint32_t *link)
{
	struct ar9300_txc *ads = AR9300TXC(ds);

	(*link) = ads->ds_link;
}
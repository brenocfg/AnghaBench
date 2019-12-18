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
typedef  int /*<<< orphan*/  u8 ;
struct eapol_sm {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int eapol_sm_rx_eapol(struct eapol_sm *sm, const u8 *src,
				    const u8 *buf, size_t len)
{
	return 0;
}
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
typedef  int /*<<< orphan*/  uint8_t ;
struct ntb_child {int /*<<< orphan*/  mwcnt; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct ntb_child* device_get_ivars (int /*<<< orphan*/ ) ; 

uint8_t
ntb_mw_count(device_t ntb)
{
	struct ntb_child *nc = device_get_ivars(ntb);

	return (nc->mwcnt);
}
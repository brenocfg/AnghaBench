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

/* Variables and functions */
 int /*<<< orphan*/  BT_ERR (char*,int,int,int,int) ; 

__attribute__((used)) static inline void ath3k_log_failed_loading(int err, int len, int size,
					    int count)
{
	BT_ERR("Firmware loading err = %d, len = %d, size = %d, count = %d",
	       err, len, size, count);
}
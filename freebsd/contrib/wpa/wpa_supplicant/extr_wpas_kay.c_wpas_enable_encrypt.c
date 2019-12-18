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
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
 int wpa_drv_enable_encrypt (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wpas_enable_encrypt(void *wpa_s, Boolean enabled)
{
	return wpa_drv_enable_encrypt(wpa_s, enabled);
}
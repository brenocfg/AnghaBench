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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int wpa_drv_set_current_cipher_suite (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wpas_set_current_cipher_suite(void *wpa_s, u64 cs)
{
	return wpa_drv_set_current_cipher_suite(wpa_s, cs);
}
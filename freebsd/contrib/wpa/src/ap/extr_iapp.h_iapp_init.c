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
struct iapp_data {int dummy; } ;
struct hostapd_data {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct iapp_data * iapp_init(struct hostapd_data *hapd,
					   const char *iface)
{
	return NULL;
}
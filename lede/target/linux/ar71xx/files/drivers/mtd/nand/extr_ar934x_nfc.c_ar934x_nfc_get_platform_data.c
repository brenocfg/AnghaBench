#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ar934x_nfc_platform_data {int dummy; } ;
struct ar934x_nfc {TYPE_1__* parent; } ;
struct TYPE_2__ {struct ar934x_nfc_platform_data* platform_data; } ;

/* Variables and functions */

__attribute__((used)) static inline struct ar934x_nfc_platform_data *
ar934x_nfc_get_platform_data(struct ar934x_nfc *nfc)
{
	return nfc->parent->platform_data;
}
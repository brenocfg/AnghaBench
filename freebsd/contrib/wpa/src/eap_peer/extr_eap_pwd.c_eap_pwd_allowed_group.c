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
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  range; } ;
struct eap_pwd_data {TYPE_1__ allowed_groups; } ;

/* Variables and functions */
 int freq_range_list_includes (TYPE_1__*,int) ; 

__attribute__((used)) static int eap_pwd_allowed_group(struct eap_pwd_data *data, u16 group)
{
	if (!data->allowed_groups.range) {
		/* By default, allow the groups using NIST curves P-256, P-384,
		 * and P-521. */
		return group == 19 || group == 20 || group == 21;
	}

	return freq_range_list_includes(&data->allowed_groups, group);
}
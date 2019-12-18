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
struct i2c_client {int dummy; } ;
typedef  enum si5351_variant { ____Placeholder_si5351_variant } si5351_variant ;

/* Variables and functions */

__attribute__((used)) static int si5351_dt_parse(struct i2c_client *client, enum si5351_variant variant)
{
	return 0;
}
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
struct vegas {int slow_start_toggle; } ;
struct cc_var {struct vegas* cc_data; } ;

/* Variables and functions */

__attribute__((used)) static void
vegas_conn_init(struct cc_var *ccv)
{
	struct vegas *vegas_data;

	vegas_data = ccv->cc_data;
	vegas_data->slow_start_toggle = 1;
}
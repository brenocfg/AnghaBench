#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ lid2guid; } ;
typedef  TYPE_1__ f_internal_t ;

/* Variables and functions */
 int /*<<< orphan*/  g_hash_table_destroy (scalar_t__) ; 

void destroy_lid2guid(f_internal_t *f_int)
{
	if (f_int->lid2guid) {
		g_hash_table_destroy(f_int->lid2guid);
	}
}
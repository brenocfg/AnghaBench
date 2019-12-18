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
typedef  int /*<<< orphan*/  heim_any_set ;

/* Variables and functions */
 int /*<<< orphan*/  der_free_octet_string (int /*<<< orphan*/ *) ; 

void
free_heim_any_set(heim_any_set *data)
{
    der_free_octet_string(data);
}
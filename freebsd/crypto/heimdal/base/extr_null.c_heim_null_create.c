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
typedef  int /*<<< orphan*/  heim_null_t ;

/* Variables and functions */
 int /*<<< orphan*/  HEIM_TID_NULL ; 
 int /*<<< orphan*/  heim_base_make_tagged_object (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

heim_null_t
heim_null_create(void)
{
    return heim_base_make_tagged_object(0, HEIM_TID_NULL);
}
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
typedef  int /*<<< orphan*/  ijk_inject_callback ;

/* Variables and functions */
 int /*<<< orphan*/  ffp_global_set_inject_callback (int /*<<< orphan*/ ) ; 

void ijkmp_global_set_inject_callback(ijk_inject_callback cb)
{
    ffp_global_set_inject_callback(cb);
}
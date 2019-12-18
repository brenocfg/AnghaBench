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
typedef  int /*<<< orphan*/  xo_ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  xo_finish_h (int /*<<< orphan*/ *) ; 

xo_ssize_t
xo_finish (void)
{
    return xo_finish_h(NULL);
}
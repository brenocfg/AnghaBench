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
typedef  int /*<<< orphan*/  h2o_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_buffer_dispose (int /*<<< orphan*/ **) ; 

void h2o_buffer__dispose_linked(void *p)
{
    h2o_buffer_t **buf = p;
    h2o_buffer_dispose(buf);
}
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
struct resource {int /*<<< orphan*/  r_bushandle; } ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */

bus_space_handle_t
rman_get_bushandle(struct resource *r)
{

	return (r->r_bushandle);
}
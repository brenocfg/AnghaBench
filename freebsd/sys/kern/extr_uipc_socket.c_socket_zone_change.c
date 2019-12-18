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

/* Variables and functions */
 int /*<<< orphan*/  maxsockets ; 
 int /*<<< orphan*/  socket_zone ; 
 int /*<<< orphan*/  uma_zone_set_max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
socket_zone_change(void *tag)
{

	maxsockets = uma_zone_set_max(socket_zone, maxsockets);
}
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
typedef  int /*<<< orphan*/  h2o_tunnel_t ;

/* Variables and functions */
 int /*<<< orphan*/  close_connection (int /*<<< orphan*/ *) ; 

void h2o_tunnel_break(h2o_tunnel_t *tunnel)
{
    close_connection(tunnel);
}
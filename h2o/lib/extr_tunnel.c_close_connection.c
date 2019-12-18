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
struct st_h2o_tunnel_t {int /*<<< orphan*/ * sock; int /*<<< orphan*/  timeout_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct st_h2o_tunnel_t*) ; 
 int /*<<< orphan*/  h2o_socket_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_timer_unlink (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void close_connection(struct st_h2o_tunnel_t *tunnel)
{
    h2o_timer_unlink(&tunnel->timeout_entry);

    h2o_socket_close(tunnel->sock[0]);
    h2o_socket_close(tunnel->sock[1]);

    free(tunnel);
}
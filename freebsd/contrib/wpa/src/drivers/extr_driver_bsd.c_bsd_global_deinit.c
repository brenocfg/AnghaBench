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
struct bsd_driver_global {int /*<<< orphan*/  sock; int /*<<< orphan*/  route; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eloop_unregister_read_sock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (struct bsd_driver_global*) ; 

__attribute__((used)) static void
bsd_global_deinit(void *priv)
{
	struct bsd_driver_global *global = priv;

	eloop_unregister_read_sock(global->route);
	(void) close(global->route);
	(void) close(global->sock);
	os_free(global);
}
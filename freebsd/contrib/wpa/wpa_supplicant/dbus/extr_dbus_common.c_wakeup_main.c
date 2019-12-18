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
struct wpas_dbus_priv {int should_dispatch; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGPOLL ; 
 int /*<<< orphan*/  raise (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wakeup_main(void *data)
{
	struct wpas_dbus_priv *priv = data;

	/* Use SIGPOLL to break out of the eloop select() */
	raise(SIGPOLL);
	priv->should_dispatch = 1;
}
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
struct ssh {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug (char*) ; 

__attribute__((used)) static void
client_cleanup_stdio_fwd(struct ssh *ssh, int id, void *arg)
{
	debug("stdio forwarding: done");
	cleanup_exit(0);
}
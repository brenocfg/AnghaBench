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
struct cuse_server {int dummy; } ;

/* Variables and functions */
 int cuse_server_do_close (struct cuse_server*) ; 
 int /*<<< orphan*/  cuse_server_unref (struct cuse_server*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  pause (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cuse_server_free(void *arg)
{
	struct cuse_server *pcs = arg;

	/*
	 * The final server unref should be done by the server thread
	 * to prevent deadlock in the client cdevpriv destructor,
	 * which cannot destroy itself.
	 */
	while (cuse_server_do_close(pcs) != 1)
		pause("W", hz);

	/* drop final refcount */
	cuse_server_unref(pcs);
}
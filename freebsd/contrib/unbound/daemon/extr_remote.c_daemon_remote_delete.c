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
struct daemon_remote {scalar_t__ ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_CTX_free (scalar_t__) ; 
 int /*<<< orphan*/  daemon_remote_clear (struct daemon_remote*) ; 
 int /*<<< orphan*/  free (struct daemon_remote*) ; 

void daemon_remote_delete(struct daemon_remote* rc)
{
	if(!rc) return;
	daemon_remote_clear(rc);
	if(rc->ctx) {
		SSL_CTX_free(rc->ctx);
	}
	free(rc);
}
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
typedef  int /*<<< orphan*/  Authctxt ;

/* Variables and functions */
 int /*<<< orphan*/  server_loop2 (struct ssh*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
do_authenticated2(struct ssh *ssh, Authctxt *authctxt)
{
	server_loop2(ssh, authctxt);
}
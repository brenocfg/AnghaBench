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
typedef  int uint32_t ;
struct rumpclient_fork {int dummy; } ;

/* Variables and functions */
 scalar_t__ ESRCH ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int rumpclient_fork_init (struct rumpclient_fork*) ; 
 struct rumpclient_fork* rumpclient_prefork () ; 

__attribute__((used)) static void
fakeauth(void)
{
	struct rumpclient_fork *rf;
	uint32_t *auth;
	int rv;

	if ((rf = rumpclient_prefork()) == NULL)
		err(1, "prefork");

	/* XXX: we know the internal structure of rf */
	auth = (void *)rf;
	*(auth+3) = *(auth+3) ^ 0x1;

	rv = rumpclient_fork_init(rf);
	if (!(rv == -1 && errno == ESRCH))
		exit(1);
}
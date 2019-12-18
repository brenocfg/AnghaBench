#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * banner; } ;

/* Variables and functions */
 char* PRIVSEP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  auth2_read_banner () ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_1__ options ; 
 int /*<<< orphan*/  userauth_send_banner (char*) ; 

__attribute__((used)) static void
userauth_banner(void)
{
	char *banner = NULL;

	if (options.banner == NULL)
		return;

	if ((banner = PRIVSEP(auth2_read_banner())) == NULL)
		goto done;
	userauth_send_banner(banner);

done:
	free(banner);
}
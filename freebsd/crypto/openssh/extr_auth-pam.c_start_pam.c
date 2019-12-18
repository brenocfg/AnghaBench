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
struct TYPE_2__ {int /*<<< orphan*/  use_pam; } ;
typedef  int /*<<< orphan*/  Authctxt ;

/* Variables and functions */
 int /*<<< orphan*/  fatal (char*) ; 
 TYPE_1__ options ; 
 int sshpam_init (int /*<<< orphan*/ *) ; 

void
start_pam(Authctxt *authctxt)
{
	if (!options.use_pam)
		fatal("PAM: initialisation requested when UsePAM=no");

	if (sshpam_init(authctxt) == -1)
		fatal("PAM: initialisation failed");
}
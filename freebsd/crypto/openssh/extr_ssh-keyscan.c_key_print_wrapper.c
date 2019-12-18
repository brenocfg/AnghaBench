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
struct sshkey {int dummy; } ;
struct ssh {int dummy; } ;
typedef  int /*<<< orphan*/  con ;

/* Variables and functions */
 int /*<<< orphan*/  keyprint (int /*<<< orphan*/ *,struct sshkey*) ; 
 int /*<<< orphan*/ * ssh_get_app_data (struct ssh*) ; 

__attribute__((used)) static int
key_print_wrapper(struct sshkey *hostkey, struct ssh *ssh)
{
	con *c;

	if ((c = ssh_get_app_data(ssh)) != NULL)
		keyprint(c, hostkey);
	/* always abort key exchange */
	return -1;
}
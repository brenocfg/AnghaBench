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

/* Variables and functions */
 int /*<<< orphan*/  fatal (char*) ; 
 int verify_host_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sshkey*) ; 
 int /*<<< orphan*/  xxx_host ; 
 int /*<<< orphan*/  xxx_hostaddr ; 

__attribute__((used)) static int
verify_host_key_callback(struct sshkey *hostkey, struct ssh *ssh)
{
	if (verify_host_key(xxx_host, xxx_hostaddr, hostkey) == -1)
		fatal("Host key verification failed.");
	return 0;
}
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
struct sshkey {TYPE_1__* cert; } ;
struct TYPE_2__ {int /*<<< orphan*/  critical; } ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*,char const*) ; 
 scalar_t__ sshbuf_len (int /*<<< orphan*/ ) ; 
 scalar_t__ sshkey_cert_check_authority (struct sshkey const*,int,int /*<<< orphan*/ ,char const*,char const**) ; 

__attribute__((used)) static int
check_host_cert(const char *host, const struct sshkey *host_key)
{
	const char *reason;

	if (sshkey_cert_check_authority(host_key, 1, 0, host, &reason) != 0) {
		error("%s", reason);
		return 0;
	}
	if (sshbuf_len(host_key->cert->critical) != 0) {
		error("Certificate for %s contains unsupported "
		    "critical options(s)", host);
		return 0;
	}
	return 1;
}
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

/* Variables and functions */
 int /*<<< orphan*/  export_dns_rr (char const*,struct sshkey*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  get_cert ; 
 scalar_t__ hash_hosts ; 
 char* host_hash (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lowercase (char*) ; 
 scalar_t__ print_sshfp ; 
 char* put_host_port (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssh_port ; 
 int /*<<< orphan*/  sshkey_write (struct sshkey*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
keyprint_one(const char *host, struct sshkey *key)
{
	char *hostport;
	const char *known_host, *hashed;

	if (print_sshfp) {
		export_dns_rr(host, key, stdout, 0);
		return;
	}

	hostport = put_host_port(host, ssh_port);
	lowercase(hostport);
	if (hash_hosts && (hashed = host_hash(host, NULL, 0)) == NULL)
		fatal("host_hash failed");
	known_host = hash_hosts ? hashed : hostport;
	if (!get_cert)
		fprintf(stdout, "%s ", known_host);
	sshkey_write(key, stdout);
	fputs("\n", stdout);
	free(hostport);
}
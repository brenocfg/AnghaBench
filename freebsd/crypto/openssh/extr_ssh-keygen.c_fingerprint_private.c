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
struct stat {int dummy; } ;
struct sshkey {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fatal (char*,char const*,...) ; 
 int /*<<< orphan*/  fingerprint_one_key (struct sshkey*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  identity_file ; 
 int /*<<< orphan*/  ssh_err (int) ; 
 int /*<<< orphan*/  sshkey_free (struct sshkey*) ; 
 int sshkey_load_private (char const*,int /*<<< orphan*/ *,struct sshkey**,char**) ; 
 int sshkey_load_public (char const*,struct sshkey**,char**) ; 
 scalar_t__ stat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fingerprint_private(const char *path)
{
	struct stat st;
	char *comment = NULL;
	struct sshkey *public = NULL;
	int r;

	if (stat(identity_file, &st) < 0)
		fatal("%s: %s", path, strerror(errno));
	if ((r = sshkey_load_public(path, &public, &comment)) != 0) {
		debug("load public \"%s\": %s", path, ssh_err(r));
		if ((r = sshkey_load_private(path, NULL,
		    &public, &comment)) != 0) {
			debug("load private \"%s\": %s", path, ssh_err(r));
			fatal("%s is not a key file.", path);
		}
	}

	fingerprint_one_key(public, comment);
	sshkey_free(public);
	free(comment);
}
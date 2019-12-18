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
struct mntarg {int dummy; } ;

/* Variables and functions */
 int EDOOFUS ; 
 int ENOENT ; 
 int ERRMSGL ; 
 int /*<<< orphan*/  MNT_ROOTFS ; 
 int /*<<< orphan*/  M_TEMP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int hz ; 
 int kernel_mount (struct mntarg*,int /*<<< orphan*/ ) ; 
 char* malloc (int,int /*<<< orphan*/ ,int) ; 
 struct mntarg* mount_arg (struct mntarg*,char*,char*,int) ; 
 int /*<<< orphan*/  parse_advance (char**) ; 
 struct mntarg* parse_mountroot_options (struct mntarg*,char*) ; 
 int /*<<< orphan*/  parse_poke (char**,char) ; 
 int parse_skipto (char**,char) ; 
 int parse_token (char**,char**) ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int root_mount_mddev ; 
 int root_mount_timeout ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 char* strstr (char*,char*) ; 
 int /*<<< orphan*/ * vfs_byname (char*) ; 
 int vfs_mountroot_wait_if_neccessary (char*,char*) ; 

__attribute__((used)) static int
parse_mount(char **conf)
{
	char *errmsg;
	struct mntarg *ma;
	char *dev, *fs, *opts, *tok;
	int delay, error, timeout;

	error = parse_token(conf, &tok);
	if (error)
		return (error);
	fs = tok;
	error = parse_skipto(&tok, ':');
	if (error) {
		free(fs, M_TEMP);
		return (error);
	}
	parse_poke(&tok, '\0');
	parse_advance(&tok);
	dev = tok;

	if (root_mount_mddev != -1) {
		/* Handle substitution for the md unit number. */
		tok = strstr(dev, "md#");
		if (tok != NULL)
			tok[2] = '0' + root_mount_mddev;
	}

	/* Parse options. */
	error = parse_token(conf, &tok);
	opts = (error == 0) ? tok : NULL;

	printf("Trying to mount root from %s:%s [%s]...\n", fs, dev,
	    (opts != NULL) ? opts : "");

	errmsg = malloc(ERRMSGL, M_TEMP, M_WAITOK | M_ZERO);

	if (vfs_byname(fs) == NULL) {
		strlcpy(errmsg, "unknown file system", ERRMSGL);
		error = ENOENT;
		goto out;
	}

	error = vfs_mountroot_wait_if_neccessary(fs, dev);
	if (error != 0)
		goto out;

	delay = hz / 10;
	timeout = root_mount_timeout * hz;

	for (;;) {
		ma = NULL;
		ma = mount_arg(ma, "fstype", fs, -1);
		ma = mount_arg(ma, "fspath", "/", -1);
		ma = mount_arg(ma, "from", dev, -1);
		ma = mount_arg(ma, "errmsg", errmsg, ERRMSGL);
		ma = mount_arg(ma, "ro", NULL, 0);
		ma = parse_mountroot_options(ma, opts);

		error = kernel_mount(ma, MNT_ROOTFS);
		if (error == 0 || timeout <= 0)
			break;

		if (root_mount_timeout * hz == timeout ||
		    (bootverbose && timeout % hz == 0)) {
			printf("Mounting from %s:%s failed with error %d; "
			    "retrying for %d more second%s\n", fs, dev, error,
			    timeout / hz, (timeout / hz > 1) ? "s" : "");
		}
		pause("rmretry", delay);
		timeout -= delay;
	}
 out:
	if (error) {
		printf("Mounting from %s:%s failed with error %d",
		    fs, dev, error);
		if (errmsg[0] != '\0')
			printf(": %s", errmsg);
		printf(".\n");
	}
	free(fs, M_TEMP);
	free(errmsg, M_TEMP);
	if (opts != NULL)
		free(opts, M_TEMP);
	/* kernel_mount can return -1 on error. */
	return ((error < 0) ? EDOOFUS : error);
}
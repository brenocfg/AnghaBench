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
struct sshbuf {int dummy; } ;
struct ssh_krl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssh_err (int) ; 
 int ssh_krl_from_blob (struct sshbuf*,struct ssh_krl**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sshbuf_free (struct sshbuf*) ; 
 struct sshbuf* sshbuf_new () ; 
 int sshkey_load_file (int,struct sshbuf*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
load_krl(const char *path, struct ssh_krl **krlp)
{
	struct sshbuf *krlbuf;
	int r, fd;

	if ((krlbuf = sshbuf_new()) == NULL)
		fatal("sshbuf_new failed");
	if ((fd = open(path, O_RDONLY)) == -1)
		fatal("open %s: %s", path, strerror(errno));
	if ((r = sshkey_load_file(fd, krlbuf)) != 0)
		fatal("Unable to load KRL: %s", ssh_err(r));
	close(fd);
	/* XXX check sigs */
	if ((r = ssh_krl_from_blob(krlbuf, krlp, NULL, 0)) != 0 ||
	    *krlp == NULL)
		fatal("Invalid KRL file: %s", ssh_err(r));
	sshbuf_free(krlbuf);
}
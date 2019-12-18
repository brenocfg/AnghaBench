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

/* Variables and functions */
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int SSH_ERR_SYSTEM_ERROR ; 
 scalar_t__ atomicio (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int open (char const*,int,int) ; 
 scalar_t__ sshbuf_len (struct sshbuf*) ; 
 int /*<<< orphan*/  sshbuf_mutable_ptr (struct sshbuf*) ; 
 int /*<<< orphan*/  unlink (char const*) ; 
 int /*<<< orphan*/  vwrite ; 

__attribute__((used)) static int
sshkey_save_private_blob(struct sshbuf *keybuf, const char *filename)
{
	int fd, oerrno;

	if ((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600)) < 0)
		return SSH_ERR_SYSTEM_ERROR;
	if (atomicio(vwrite, fd, sshbuf_mutable_ptr(keybuf),
	    sshbuf_len(keybuf)) != sshbuf_len(keybuf)) {
		oerrno = errno;
		close(fd);
		unlink(filename);
		errno = oerrno;
		return SSH_ERR_SYSTEM_ERROR;
	}
	close(fd);
	return 0;
}
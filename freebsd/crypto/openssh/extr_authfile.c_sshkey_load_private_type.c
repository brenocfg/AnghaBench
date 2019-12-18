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
 int /*<<< orphan*/  O_RDONLY ; 
 int SSH_ERR_KEY_BAD_PERMISSIONS ; 
 int SSH_ERR_SYSTEM_ERROR ; 
 int /*<<< orphan*/  close (int) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int sshkey_load_private_type_fd (int,int,char const*,struct sshkey**,char**) ; 
 scalar_t__ sshkey_perm_ok (int,char const*) ; 
 int sshkey_set_filename (struct sshkey*,char const*) ; 

int
sshkey_load_private_type(int type, const char *filename, const char *passphrase,
    struct sshkey **keyp, char **commentp, int *perm_ok)
{
	int fd, r;

	if (keyp != NULL)
		*keyp = NULL;
	if (commentp != NULL)
		*commentp = NULL;

	if ((fd = open(filename, O_RDONLY)) < 0) {
		if (perm_ok != NULL)
			*perm_ok = 0;
		return SSH_ERR_SYSTEM_ERROR;
	}
	if (sshkey_perm_ok(fd, filename) != 0) {
		if (perm_ok != NULL)
			*perm_ok = 0;
		r = SSH_ERR_KEY_BAD_PERMISSIONS;
		goto out;
	}
	if (perm_ok != NULL)
		*perm_ok = 1;

	r = sshkey_load_private_type_fd(fd, type, passphrase, keyp, commentp);
	if (r == 0 && keyp && *keyp)
		r = sshkey_set_filename(*keyp, filename);
 out:
	close(fd);
	return r;
}
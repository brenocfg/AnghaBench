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
 int /*<<< orphan*/  KEY_UNSPEC ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  sshkey_free (struct sshkey*) ; 
 struct sshkey* sshkey_new (int /*<<< orphan*/ ) ; 
 int sshkey_read (struct sshkey*,char**) ; 

__attribute__((used)) static struct sshkey *
try_read_key(char **cpp)
{
	struct sshkey *ret;
	int r;

	if ((ret = sshkey_new(KEY_UNSPEC)) == NULL)
		fatal("sshkey_new failed");
	if ((r = sshkey_read(ret, cpp)) == 0)
		return ret;
	/* Not a key */
	sshkey_free(ret);
	return NULL;
}
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
struct pkcs11_keyinfo {int /*<<< orphan*/  key; struct pkcs11_keyinfo* providername; } ;

/* Variables and functions */
 struct pkcs11_keyinfo* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct pkcs11_keyinfo* TAILQ_NEXT (struct pkcs11_keyinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct pkcs11_keyinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct pkcs11_keyinfo*) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  pkcs11_keylist ; 
 int /*<<< orphan*/  sshkey_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (struct pkcs11_keyinfo*,char*) ; 

__attribute__((used)) static void
del_keys_by_name(char *name)
{
	struct pkcs11_keyinfo *ki, *nxt;

	for (ki = TAILQ_FIRST(&pkcs11_keylist); ki; ki = nxt) {
		nxt = TAILQ_NEXT(ki, next);
		if (!strcmp(ki->providername, name)) {
			TAILQ_REMOVE(&pkcs11_keylist, ki, next);
			free(ki->providername);
			sshkey_free(ki->key);
			free(ki);
		}
	}
}
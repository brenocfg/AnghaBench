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
struct pkcs11_keyinfo {struct sshkey* key; int /*<<< orphan*/  providername; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct pkcs11_keyinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  pkcs11_keylist ; 
 struct pkcs11_keyinfo* xcalloc (int,int) ; 
 int /*<<< orphan*/  xstrdup (char*) ; 

__attribute__((used)) static void
add_key(struct sshkey *k, char *name)
{
	struct pkcs11_keyinfo *ki;

	ki = xcalloc(1, sizeof(*ki));
	ki->providername = xstrdup(name);
	ki->key = k;
	TAILQ_INSERT_TAIL(&pkcs11_keylist, ki, next);
}
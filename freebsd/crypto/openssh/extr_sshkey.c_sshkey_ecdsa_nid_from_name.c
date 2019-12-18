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
struct keytype {int type; int nid; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int KEY_ECDSA ; 
 int KEY_ECDSA_CERT ; 
 struct keytype* keytypes ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ *) ; 

int
sshkey_ecdsa_nid_from_name(const char *name)
{
	const struct keytype *kt;

	for (kt = keytypes; kt->type != -1; kt++) {
		if (kt->type != KEY_ECDSA && kt->type != KEY_ECDSA_CERT)
			continue;
		if (kt->name != NULL && strcmp(name, kt->name) == 0)
			return kt->nid;
	}
	return -1;
}
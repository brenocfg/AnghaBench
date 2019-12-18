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
struct keytype {int type; char const* name; char const* sigalg; int /*<<< orphan*/  nid; int /*<<< orphan*/  cert; } ;

/* Variables and functions */
 struct keytype* keytypes ; 
 char const* sshkey_ssh_name_from_type_nid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sshkey_type_plain (int) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

const char *
sshkey_sigalg_by_name(const char *name)
{
	const struct keytype *kt;

	for (kt = keytypes; kt->type != -1; kt++) {
		if (strcmp(kt->name, name) != 0)
			continue;
		if (kt->sigalg != NULL)
			return kt->sigalg;
		if (!kt->cert)
			return kt->name;
		return sshkey_ssh_name_from_type_nid(
		    sshkey_type_plain(kt->type), kt->nid);
	}
	return NULL;
}
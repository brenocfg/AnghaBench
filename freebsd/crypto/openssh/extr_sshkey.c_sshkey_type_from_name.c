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
struct keytype {int type; int /*<<< orphan*/  shortname; int /*<<< orphan*/  cert; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int KEY_UNSPEC ; 
 struct keytype* keytypes ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ *) ; 

int
sshkey_type_from_name(const char *name)
{
	const struct keytype *kt;

	for (kt = keytypes; kt->type != -1; kt++) {
		/* Only allow shortname matches for plain key types */
		if ((kt->name != NULL && strcmp(name, kt->name) == 0) ||
		    (!kt->cert && strcasecmp(kt->shortname, name) == 0))
			return kt->type;
	}
	return KEY_UNSPEC;
}
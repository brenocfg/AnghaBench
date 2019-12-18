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
struct keytype {int type; int nid; char const* name; } ;

/* Variables and functions */
 struct keytype* keytypes ; 

__attribute__((used)) static const char *
sshkey_ssh_name_from_type_nid(int type, int nid)
{
	const struct keytype *kt;

	for (kt = keytypes; kt->type != -1; kt++) {
		if (kt->type == type && (kt->nid == 0 || kt->nid == nid))
			return kt->name;
	}
	return "ssh-unknown";
}
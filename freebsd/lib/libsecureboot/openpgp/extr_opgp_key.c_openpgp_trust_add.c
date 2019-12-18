#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* id; } ;
typedef  TYPE_1__ OpenPGP_key ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/ * openpgp_trust_get (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  trust_list ; 
 scalar_t__ ve_anchor_verbose_get () ; 

void
openpgp_trust_add(OpenPGP_key *key)
{
	static int once = 0;

	if (!once) {
		once = 1;

		LIST_INIT(&trust_list);
	}
	if (key && openpgp_trust_get(key->id) == NULL) {
		if (ve_anchor_verbose_get())
			printf("openpgp_trust_add(%s)\n", key->id);
		LIST_INSERT_HEAD(&trust_list, key, entries);
	}
}
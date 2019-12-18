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
struct mac {int dummy; } ;
struct label_default {int /*<<< orphan*/  ld_labels; int /*<<< orphan*/  ld_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct label_default* LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct label_default* LIST_NEXT (struct label_default*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  label_default_head ; 
 int /*<<< orphan*/  ld_entries ; 
 int mac_maybe_init_internal () ; 
 int mac_prepare (struct mac**,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

int
mac_prepare_type(struct mac **mac, const char *name)
{
	struct label_default *ld;
	int error;

	error = mac_maybe_init_internal();
	if (error != 0)
		return (error);

	for (ld = LIST_FIRST(&label_default_head); ld != NULL;
	    ld = LIST_NEXT(ld, ld_entries)) {
		if (strcmp(name, ld->ld_name) == 0)
			return (mac_prepare(mac, ld->ld_labels));
	}

	errno = ENOENT;
	return (-1);		/* XXXMAC: ENOLABEL */
}
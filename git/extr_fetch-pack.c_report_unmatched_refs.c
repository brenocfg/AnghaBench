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
struct ref {int match_status; int /*<<< orphan*/  name; } ;

/* Variables and functions */
#define  REF_MATCHED 130 
#define  REF_NOT_MATCHED 129 
#define  REF_UNADVERTISED_NOT_ALLOWED 128 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int report_unmatched_refs(struct ref **sought, int nr_sought)
{
	int i, ret = 0;

	for (i = 0; i < nr_sought; i++) {
		if (!sought[i])
			continue;
		switch (sought[i]->match_status) {
		case REF_MATCHED:
			continue;
		case REF_NOT_MATCHED:
			error(_("no such remote ref %s"), sought[i]->name);
			break;
		case REF_UNADVERTISED_NOT_ALLOWED:
			error(_("Server does not allow request for unadvertised object %s"),
			      sought[i]->name);
			break;
		}
		ret = 1;
	}
	return ret;
}
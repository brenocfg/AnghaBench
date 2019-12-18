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
struct label_default {struct label_default* ld_labels; struct label_default* ld_name; } ;

/* Variables and functions */
 struct label_default* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct label_default*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct label_default*) ; 
 int /*<<< orphan*/  label_default_head ; 
 int /*<<< orphan*/  ld_entries ; 

__attribute__((used)) static void
mac_destroy_labels(void)
{
	struct label_default *ld;

	while ((ld = LIST_FIRST(&label_default_head))) {
		free(ld->ld_name);
		free(ld->ld_labels);
		LIST_REMOVE(ld, ld_entries);
		free(ld);
	}
}
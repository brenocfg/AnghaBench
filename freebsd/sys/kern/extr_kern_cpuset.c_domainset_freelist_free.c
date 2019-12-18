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
struct domainset {int dummy; } ;
struct domainlist {int dummy; } ;

/* Variables and functions */
 struct domainset* LIST_FIRST (struct domainlist*) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct domainset*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  domainset_zone ; 
 int /*<<< orphan*/  ds_link ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct domainset*) ; 

__attribute__((used)) static void
domainset_freelist_free(struct domainlist *list)
{
	struct domainset *set;

	while ((set = LIST_FIRST(list)) != NULL) {
		LIST_REMOVE(set, ds_link);
		uma_zfree(domainset_zone, set);
	}
}
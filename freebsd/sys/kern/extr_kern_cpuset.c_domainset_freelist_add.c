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
 int /*<<< orphan*/  LIST_INSERT_HEAD (struct domainlist*,struct domainset*,int /*<<< orphan*/ ) ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  domainset_zone ; 
 int /*<<< orphan*/  ds_link ; 
 struct domainset* uma_zalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
domainset_freelist_add(struct domainlist *list, int count)
{
	struct domainset *set;
	int i;

	for (i = 0; i < count; i++) {
		set = uma_zalloc(domainset_zone, M_ZERO | M_WAITOK);
		LIST_INSERT_HEAD(list, set, ds_link);
	}
}
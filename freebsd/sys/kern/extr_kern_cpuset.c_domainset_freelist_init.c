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
struct domainlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (struct domainlist*) ; 
 int /*<<< orphan*/  domainset_freelist_add (struct domainlist*,int) ; 

__attribute__((used)) static void
domainset_freelist_init(struct domainlist *list, int count)
{

	LIST_INIT(list);
	domainset_freelist_add(list, count);
}
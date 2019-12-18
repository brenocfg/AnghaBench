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
struct acl_list {int /*<<< orphan*/  region; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct acl_list*) ; 
 int /*<<< orphan*/  regional_destroy (int /*<<< orphan*/ ) ; 

void 
acl_list_delete(struct acl_list* acl)
{
	if(!acl) 
		return;
	regional_destroy(acl->region);
	free(acl);
}
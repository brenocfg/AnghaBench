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
 int /*<<< orphan*/  acl_list_delete (struct acl_list*) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  regional_create () ; 

struct acl_list* 
acl_list_create(void)
{
	struct acl_list* acl = (struct acl_list*)calloc(1,
		sizeof(struct acl_list));
	if(!acl)
		return NULL;
	acl->region = regional_create();
	if(!acl->region) {
		acl_list_delete(acl);
		return NULL;
	}
	return acl;
}
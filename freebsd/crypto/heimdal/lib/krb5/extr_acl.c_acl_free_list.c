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
struct acl_field {struct acl_field* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct acl_field*) ; 
 int /*<<< orphan*/  free_retv (struct acl_field*) ; 

__attribute__((used)) static void
acl_free_list(struct acl_field *acl, int retv)
{
    struct acl_field *next;
    if (retv)
	free_retv(acl);
    while(acl != NULL) {
	next = acl->next;
	free(acl);
	acl = next;
    }
}
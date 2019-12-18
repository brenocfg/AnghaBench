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
typedef  enum acl_type { ____Placeholder_acl_type } acl_type ;
typedef  int /*<<< orphan*/  aclent_t ;
struct TYPE_4__ {int acl_type; int acl_entry_size; scalar_t__ acl_cnt; int /*<<< orphan*/ * acl_aclp; } ;
typedef  TYPE_1__ acl_t ;
typedef  int /*<<< orphan*/  ace_t ;

/* Variables and functions */
#define  ACE_T 129 
#define  ACLENT_T 128 
 int /*<<< orphan*/  acl_free (TYPE_1__*) ; 
 scalar_t__ cacl_malloc (void**,int) ; 

acl_t *
acl_alloc(enum acl_type type)
{
	acl_t *aclp;

	if (cacl_malloc((void **)&aclp, sizeof (acl_t)) != 0)
		return (NULL);

	aclp->acl_aclp = NULL;
	aclp->acl_cnt = 0;

	switch (type) {
	case ACE_T:
		aclp->acl_type = ACE_T;
		aclp->acl_entry_size = sizeof (ace_t);
		break;
	case ACLENT_T:
		aclp->acl_type = ACLENT_T;
		aclp->acl_entry_size = sizeof (aclent_t);
		break;
	default:
		acl_free(aclp);
		aclp = NULL;
	}
	return (aclp);
}
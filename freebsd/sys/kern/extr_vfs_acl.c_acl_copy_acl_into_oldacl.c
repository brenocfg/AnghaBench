#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct oldacl {int acl_cnt; TYPE_1__* acl_entry; } ;
struct acl {scalar_t__ acl_cnt; TYPE_2__* acl_entry; } ;
struct TYPE_4__ {int /*<<< orphan*/  ae_perm; int /*<<< orphan*/  ae_id; int /*<<< orphan*/  ae_tag; } ;
struct TYPE_3__ {int /*<<< orphan*/  ae_perm; int /*<<< orphan*/  ae_id; int /*<<< orphan*/  ae_tag; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ OLDACL_MAX_ENTRIES ; 
 int /*<<< orphan*/  bzero (struct oldacl*,int) ; 

int
acl_copy_acl_into_oldacl(const struct acl *source, struct oldacl *dest)
{
	int i;

	if (source->acl_cnt > OLDACL_MAX_ENTRIES)
		return (EINVAL);

	bzero(dest, sizeof(*dest));

	dest->acl_cnt = source->acl_cnt;

	for (i = 0; i < dest->acl_cnt; i++) {
		dest->acl_entry[i].ae_tag = source->acl_entry[i].ae_tag;
		dest->acl_entry[i].ae_id = source->acl_entry[i].ae_id;
		dest->acl_entry[i].ae_perm = source->acl_entry[i].ae_perm;
	}

	return (0);
}
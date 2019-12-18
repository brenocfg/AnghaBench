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
struct rdtgroup {int /*<<< orphan*/  kn; } ;
struct kernfs_node {int dummy; } ;
struct iattr {int /*<<< orphan*/  ia_mode; int /*<<< orphan*/  ia_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_MODE ; 
 int ENOENT ; 
#define  KERNFS_DIR 130 
#define  KERNFS_FILE 129 
#define  KERNFS_LINK 128 
 int /*<<< orphan*/  S_IFDIR ; 
 int /*<<< orphan*/  S_IFLNK ; 
 int /*<<< orphan*/  S_IFREG ; 
 struct kernfs_node* kernfs_find_and_get_ns (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kernfs_put (struct kernfs_node*) ; 
 int kernfs_setattr (struct kernfs_node*,struct iattr*) ; 
 int kernfs_type (struct kernfs_node*) ; 

int rdtgroup_kn_mode_restrict(struct rdtgroup *r, const char *name)
{
	struct iattr iattr = {.ia_valid = ATTR_MODE,};
	struct kernfs_node *kn;
	int ret = 0;

	kn = kernfs_find_and_get_ns(r->kn, name, NULL);
	if (!kn)
		return -ENOENT;

	switch (kernfs_type(kn)) {
	case KERNFS_DIR:
		iattr.ia_mode = S_IFDIR;
		break;
	case KERNFS_FILE:
		iattr.ia_mode = S_IFREG;
		break;
	case KERNFS_LINK:
		iattr.ia_mode = S_IFLNK;
		break;
	}

	ret = kernfs_setattr(kn, &iattr);
	kernfs_put(kn);
	return ret;
}
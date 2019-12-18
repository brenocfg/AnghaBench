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
struct vnode {int dummy; } ;
struct ucred {int dummy; } ;
struct mac_mls {int mm_flags; } ;
struct label {int dummy; } ;
typedef  int /*<<< orphan*/  mm_temp ;

/* Variables and functions */
 int /*<<< orphan*/  IO_NODELOCKED ; 
 int /*<<< orphan*/  MAC_MLS_EXTATTR_NAME ; 
 int /*<<< orphan*/  MAC_MLS_EXTATTR_NAMESPACE ; 
 int MAC_MLS_FLAG_EFFECTIVE ; 
 struct mac_mls* SLOT (struct label*) ; 
 int /*<<< orphan*/  bzero (struct mac_mls*,size_t) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  mls_copy_effective (struct mac_mls*,struct mac_mls*) ; 
 int vn_extattr_set (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mls_vnode_setlabel_extattr(struct ucred *cred, struct vnode *vp,
    struct label *vplabel, struct label *intlabel)
{
	struct mac_mls *source, mm_temp;
	size_t buflen;
	int error;

	buflen = sizeof(mm_temp);
	bzero(&mm_temp, buflen);

	source = SLOT(intlabel);
	if ((source->mm_flags & MAC_MLS_FLAG_EFFECTIVE) == 0)
		return (0);

	mls_copy_effective(source, &mm_temp);

	error = vn_extattr_set(vp, IO_NODELOCKED, MAC_MLS_EXTATTR_NAMESPACE,
	    MAC_MLS_EXTATTR_NAME, buflen, (char *) &mm_temp, curthread);
	return (error);
}
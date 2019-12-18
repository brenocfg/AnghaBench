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
struct mac_biba {int mb_flags; } ;
struct label {int dummy; } ;
typedef  int /*<<< orphan*/  mb_temp ;

/* Variables and functions */
 int /*<<< orphan*/  IO_NODELOCKED ; 
 int /*<<< orphan*/  MAC_BIBA_EXTATTR_NAME ; 
 int /*<<< orphan*/  MAC_BIBA_EXTATTR_NAMESPACE ; 
 int MAC_BIBA_FLAG_EFFECTIVE ; 
 struct mac_biba* SLOT (struct label*) ; 
 int /*<<< orphan*/  biba_copy_effective (struct mac_biba*,struct mac_biba*) ; 
 int /*<<< orphan*/  bzero (struct mac_biba*,size_t) ; 
 int /*<<< orphan*/  curthread ; 
 int vn_extattr_set (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
biba_vnode_setlabel_extattr(struct ucred *cred, struct vnode *vp,
    struct label *vplabel, struct label *intlabel)
{
	struct mac_biba *source, mb_temp;
	size_t buflen;
	int error;

	buflen = sizeof(mb_temp);
	bzero(&mb_temp, buflen);

	source = SLOT(intlabel);
	if ((source->mb_flags & MAC_BIBA_FLAG_EFFECTIVE) == 0)
		return (0);

	biba_copy_effective(source, &mb_temp);

	error = vn_extattr_set(vp, IO_NODELOCKED, MAC_BIBA_EXTATTR_NAMESPACE,
	    MAC_BIBA_EXTATTR_NAME, buflen, (char *) &mb_temp, curthread);
	return (error);
}
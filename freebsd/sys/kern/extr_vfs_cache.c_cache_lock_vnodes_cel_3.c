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
struct mtx {int dummy; } ;
struct celockstate {struct mtx** vlp; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 struct mtx* VP2VNODELOCK (struct vnode*) ; 
 int /*<<< orphan*/  cache_assert_vlp_locked (struct mtx*) ; 
 int /*<<< orphan*/  cache_lock_vnodes_cel_3_failures ; 
 int /*<<< orphan*/  cache_unlock_vnodes_cel (struct celockstate*) ; 
 int /*<<< orphan*/  mtx_lock (struct mtx*) ; 
 scalar_t__ mtx_trylock (struct mtx*) ; 

__attribute__((used)) static bool
cache_lock_vnodes_cel_3(struct celockstate *cel, struct vnode *vp)
{
	struct mtx *vlp;
	bool ret;

	cache_assert_vlp_locked(cel->vlp[0]);
	cache_assert_vlp_locked(cel->vlp[1]);
	MPASS(cel->vlp[2] == NULL);

	MPASS(vp != NULL);
	vlp = VP2VNODELOCK(vp);

	ret = true;
	if (vlp >= cel->vlp[1]) {
		mtx_lock(vlp);
	} else {
		if (mtx_trylock(vlp))
			goto out;
		cache_lock_vnodes_cel_3_failures++;
		cache_unlock_vnodes_cel(cel);
		if (vlp < cel->vlp[0]) {
			mtx_lock(vlp);
			mtx_lock(cel->vlp[0]);
			mtx_lock(cel->vlp[1]);
		} else {
			if (cel->vlp[0] != NULL)
				mtx_lock(cel->vlp[0]);
			mtx_lock(vlp);
			mtx_lock(cel->vlp[1]);
		}
		ret = false;
	}
out:
	cel->vlp[2] = vlp;
	return (ret);
}
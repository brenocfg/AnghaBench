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
struct nm_bridge {void* private_data; } ;
typedef  void* (* bdg_update_private_data_fn_t ) (void*,void*,int*) ;

/* Variables and functions */
 int /*<<< orphan*/  BDG_WLOCK (struct nm_bridge*) ; 
 int /*<<< orphan*/  BDG_WUNLOCK (struct nm_bridge*) ; 
 int EACCES ; 
 int EINVAL ; 
 int /*<<< orphan*/  NMG_LOCK () ; 
 int /*<<< orphan*/  NMG_UNLOCK () ; 
 int /*<<< orphan*/  nm_bdg_valid_auth_token (struct nm_bridge*,void*) ; 
 struct nm_bridge* nm_find_bridge (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
netmap_bdg_update_private_data(const char *name, bdg_update_private_data_fn_t callback,
	void *callback_data, void *auth_token)
{
	void *private_data = NULL;
	struct nm_bridge *b;
	int error = 0;

	NMG_LOCK();
	b = nm_find_bridge(name, 0 /* don't create */, NULL);
	if (!b) {
		error = EINVAL;
		goto unlock_update_priv;
	}
	if (!nm_bdg_valid_auth_token(b, auth_token)) {
		error = EACCES;
		goto unlock_update_priv;
	}
	BDG_WLOCK(b);
	private_data = callback(b->private_data, callback_data, &error);
	b->private_data = private_data;
	BDG_WUNLOCK(b);

unlock_update_priv:
	NMG_UNLOCK();
	return error;
}
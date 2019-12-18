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
struct des3_state {int /*<<< orphan*/  ds_lock; int /*<<< orphan*/  ds_session; } ;
struct cryptop {int crp_etype; int crp_flags; scalar_t__ crp_opaque; } ;

/* Variables and functions */
 int CRYPTOCAP_F_SYNC ; 
 int CRYPTO_F_DONE ; 
 int EAGAIN ; 
 int crypto_dispatch (struct cryptop*) ; 
 int crypto_ses2caps (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (struct cryptop*) ; 

__attribute__((used)) static int
des3_crypto_cb(struct cryptop *crp)
{
	int error;
	struct des3_state *ds = (struct des3_state *) crp->crp_opaque;
	
	if (crypto_ses2caps(ds->ds_session) & CRYPTOCAP_F_SYNC)
		return (0);

	error = crp->crp_etype;
	if (error == EAGAIN)
		error = crypto_dispatch(crp);
	mtx_lock(&ds->ds_lock);
	if (error || (crp->crp_flags & CRYPTO_F_DONE))
		wakeup(crp);
	mtx_unlock(&ds->ds_lock);

	return (0);
}
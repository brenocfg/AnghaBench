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
struct label {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MAC_POLICY_CHECK_NOSLEEP (int /*<<< orphan*/ ,struct label*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAC_POLICY_PERFORM_NOSLEEP (int /*<<< orphan*/ ,struct label*) ; 
 int MPC_OBJECT_SYNCACHE ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int mac_labeled ; 
 struct label* mac_labelzone_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_labelzone_free (struct label*) ; 
 int /*<<< orphan*/  syncache_destroy_label ; 
 int /*<<< orphan*/  syncache_init_label ; 

int
mac_syncache_init(struct label **label)
{
	int error;

	if (mac_labeled & MPC_OBJECT_SYNCACHE) {
		*label = mac_labelzone_alloc(M_NOWAIT);
		if (*label == NULL)
			return (ENOMEM);
		/*
		 * Since we are holding the inpcb locks the policy can not
		 * allocate policy specific label storage using M_WAITOK.  So
		 * we need to do a MAC_CHECK instead of the typical
		 * MAC_PERFORM so we can propagate allocation failures back
		 * to the syncache code.
		 */
		MAC_POLICY_CHECK_NOSLEEP(syncache_init_label, *label,
		    M_NOWAIT);
		if (error) {
			MAC_POLICY_PERFORM_NOSLEEP(syncache_destroy_label,
			    *label);
			mac_labelzone_free(*label);
		}
		return (error);
	} else
		*label = NULL;
	return (0);
}
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
struct ucred {struct label* cr_label; } ;
struct shmfd {int dummy; } ;
struct mac_mls {int dummy; } ;
struct label {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 struct mac_mls* SLOT (struct label*) ; 
 int /*<<< orphan*/  mls_dominate_effective (struct mac_mls*,struct mac_mls*) ; 
 int /*<<< orphan*/  mls_enabled ; 
 int /*<<< orphan*/  revocation_enabled ; 

__attribute__((used)) static int
mls_posixshm_check_read(struct ucred *active_cred, struct ucred *file_cred,
    struct shmfd *shm, struct label *shmlabel)
{
	struct mac_mls *subj, *obj;

	if (!mls_enabled || !revocation_enabled)
		return (0);

	subj = SLOT(active_cred->cr_label);
	obj = SLOT(shmlabel);

	if (!mls_dominate_effective(subj, obj))
		return (EACCES);

	return (0);
}
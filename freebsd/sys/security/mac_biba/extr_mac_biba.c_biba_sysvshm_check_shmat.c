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
struct shmid_kernel {int dummy; } ;
struct mac_biba {int dummy; } ;
struct label {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 int SHM_RDONLY ; 
 struct mac_biba* SLOT (struct label*) ; 
 int /*<<< orphan*/  biba_dominate_effective (struct mac_biba*,struct mac_biba*) ; 
 int /*<<< orphan*/  biba_enabled ; 

__attribute__((used)) static int
biba_sysvshm_check_shmat(struct ucred *cred, struct shmid_kernel *shmsegptr,
    struct label *shmseglabel, int shmflg)
{
	struct mac_biba *subj, *obj;

	if (!biba_enabled)
		return (0);

	subj = SLOT(cred->cr_label);
	obj = SLOT(shmseglabel);

	if (!biba_dominate_effective(obj, subj))
		return (EACCES);
	if ((shmflg & SHM_RDONLY) == 0) {
		if (!biba_dominate_effective(subj, obj))
			return (EACCES);
	}
	
	return (0);
}
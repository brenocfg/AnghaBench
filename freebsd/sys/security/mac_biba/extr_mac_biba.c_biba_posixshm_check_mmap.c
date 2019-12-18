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
struct mac_biba {int dummy; } ;
struct label {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 int MAP_SHARED ; 
 struct mac_biba* SLOT (struct label*) ; 
 int VM_PROT_EXECUTE ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 int /*<<< orphan*/  biba_dominate_effective (struct mac_biba*,struct mac_biba*) ; 
 int /*<<< orphan*/  biba_enabled ; 
 int /*<<< orphan*/  revocation_enabled ; 

__attribute__((used)) static int
biba_posixshm_check_mmap(struct ucred *cred, struct shmfd *shmfd,
    struct label *shmlabel, int prot, int flags)
{
	struct mac_biba *subj, *obj;

	if (!biba_enabled || !revocation_enabled)
		return (0);

	subj = SLOT(cred->cr_label);
	obj = SLOT(shmlabel);

	if (prot & (VM_PROT_READ | VM_PROT_EXECUTE)) {
		if (!biba_dominate_effective(obj, subj))
			return (EACCES);
	}
	if (((prot & VM_PROT_WRITE) != 0) && ((flags & MAP_SHARED) != 0)) {
		if (!biba_dominate_effective(subj, obj))
			return (EACCES);
	}

	return (0);
}
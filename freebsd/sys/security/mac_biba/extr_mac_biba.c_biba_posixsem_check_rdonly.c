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
struct mac_biba {int dummy; } ;
struct label {int dummy; } ;
struct ksem {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 struct mac_biba* SLOT (struct label*) ; 
 int /*<<< orphan*/  biba_dominate_effective (struct mac_biba*,struct mac_biba*) ; 
 int /*<<< orphan*/  biba_enabled ; 

__attribute__((used)) static int
biba_posixsem_check_rdonly(struct ucred *active_cred, struct ucred *file_cred,
    struct ksem *ks, struct label *kslabel)
{
	struct mac_biba *subj, *obj;

	if (!biba_enabled)
		return (0);

	subj = SLOT(active_cred->cr_label);
	obj = SLOT(kslabel);

	if (!biba_dominate_effective(obj, subj))
		return (EACCES);

	return (0);
}
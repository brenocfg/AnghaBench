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
struct pipepair {int dummy; } ;
struct mac_biba {int dummy; } ;
struct label {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 struct mac_biba* SLOT (struct label*) ; 
 int /*<<< orphan*/  biba_dominate_effective (struct mac_biba*,struct mac_biba*) ; 
 int /*<<< orphan*/  biba_enabled ; 

__attribute__((used)) static int
biba_pipe_check_poll(struct ucred *cred, struct pipepair *pp,
    struct label *pplabel)
{
	struct mac_biba *subj, *obj;

	if (!biba_enabled)
		return (0);

	subj = SLOT(cred->cr_label);
	obj = SLOT(pplabel);

	if (!biba_dominate_effective(obj, subj))
		return (EACCES);

	return (0);
}
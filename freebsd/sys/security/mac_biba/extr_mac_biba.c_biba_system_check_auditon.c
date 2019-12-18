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
struct ucred {int /*<<< orphan*/  cr_label; } ;
struct mac_biba {int dummy; } ;

/* Variables and functions */
 struct mac_biba* SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  biba_enabled ; 
 int biba_subject_privileged (struct mac_biba*) ; 

__attribute__((used)) static int
biba_system_check_auditon(struct ucred *cred, int cmd)
{
	struct mac_biba *subj;
	int error;

	if (!biba_enabled)
		return (0);

	subj = SLOT(cred->cr_label);

	error = biba_subject_privileged(subj);
	if (error)
		return (error);

	return (0);
}
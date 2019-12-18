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
struct mac_lomac {int dummy; } ;

/* Variables and functions */
 int ESRCH ; 
 struct mac_lomac* SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lomac_dominate_single (struct mac_lomac*,struct mac_lomac*) ; 
 int /*<<< orphan*/  lomac_enabled ; 

__attribute__((used)) static int
lomac_cred_check_visible(struct ucred *cr1, struct ucred *cr2)
{
	struct mac_lomac *subj, *obj;

	if (!lomac_enabled)
		return (0);

	subj = SLOT(cr1->cr_label);
	obj = SLOT(cr2->cr_label);

	/* XXX: range */
	if (!lomac_dominate_single(obj, subj))
		return (ESRCH);

	return (0);
}
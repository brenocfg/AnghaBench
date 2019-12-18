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
struct mac_mls {int dummy; } ;
struct label {int dummy; } ;

/* Variables and functions */
 struct mac_mls* SLOT (struct label*) ; 
 int /*<<< orphan*/  mls_copy (struct mac_mls*,struct mac_mls*) ; 

__attribute__((used)) static void
mls_cred_relabel(struct ucred *cred, struct label *newlabel)
{
	struct mac_mls *source, *dest;

	source = SLOT(newlabel);
	dest = SLOT(cred->cr_label);

	mls_copy(source, dest);
}
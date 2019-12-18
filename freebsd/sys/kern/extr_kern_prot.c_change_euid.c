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
struct uidinfo {int /*<<< orphan*/  ui_uid; } ;
struct ucred {struct uidinfo* cr_uidinfo; int /*<<< orphan*/  cr_uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  uifree (struct uidinfo*) ; 
 int /*<<< orphan*/  uihold (struct uidinfo*) ; 

void
change_euid(struct ucred *newcred, struct uidinfo *euip)
{

	newcred->cr_uid = euip->ui_uid;
	uihold(euip);
	uifree(newcred->cr_uidinfo);
	newcred->cr_uidinfo = euip;
}
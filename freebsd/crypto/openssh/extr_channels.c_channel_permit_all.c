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
struct ssh {int dummy; } ;
struct permission_set {scalar_t__ num_permitted_user; int all_permitted; } ;

/* Variables and functions */
 struct permission_set* permission_set_get (struct ssh*,int) ; 

void
channel_permit_all(struct ssh *ssh, int where)
{
	struct permission_set *pset = permission_set_get(ssh, where);

	if (pset->num_permitted_user == 0)
		pset->all_permitted = 1;
}
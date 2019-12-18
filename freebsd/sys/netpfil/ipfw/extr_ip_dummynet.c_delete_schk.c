#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dn_schk {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  schedhash; } ;

/* Variables and functions */
 int /*<<< orphan*/  DNHT_REMOVE ; 
 scalar_t__ DN_DESTROY ; 
 scalar_t__ DN_MAX_ID ; 
 int EINVAL ; 
 int /*<<< orphan*/  ND (char*,int,struct dn_schk*) ; 
 int /*<<< orphan*/  delete_fs (scalar_t__,int) ; 
 TYPE_1__ dn_cfg ; 
 struct dn_schk* dn_ht_find (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schk_delete_cb (struct dn_schk*,void*) ; 

__attribute__((used)) static int
delete_schk(int i)
{
	struct dn_schk *s;

	s = dn_ht_find(dn_cfg.schedhash, i, DNHT_REMOVE, NULL);
	ND("%d %p", i, s);
	if (!s)
		return EINVAL;
	delete_fs(i + DN_MAX_ID, 1); /* first delete internal fs */
	/* then detach flowsets, delete traffic */
	schk_delete_cb(s, (void*)(uintptr_t)DN_DESTROY);
	return 0;
}
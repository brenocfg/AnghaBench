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
struct pkcs7_signed_info {scalar_t__ authattrs; struct pkcs7_signed_info* next; } ;
struct pkcs7_message {int have_authattrs; struct pkcs7_signed_info* signed_infos; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static int pkcs7_check_authattrs(struct pkcs7_message *msg)
{
	struct pkcs7_signed_info *sinfo;
	bool want = false;

	sinfo = msg->signed_infos;
	if (!sinfo)
		goto inconsistent;

	if (sinfo->authattrs) {
		want = true;
		msg->have_authattrs = true;
	}

	for (sinfo = sinfo->next; sinfo; sinfo = sinfo->next)
		if (!!sinfo->authattrs != want)
			goto inconsistent;
	return 0;

inconsistent:
	pr_warn("Inconsistently supplied authAttrs\n");
	return -EINVAL;
}
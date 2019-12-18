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
struct nlattr {int dummy; } ;
struct nla_policy {int dummy; } ;

/* Variables and functions */
 int drbd_nla_check_mandatory (int,struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int,struct nlattr*,struct nla_policy const*,int /*<<< orphan*/ *) ; 

int drbd_nla_parse_nested(struct nlattr *tb[], int maxtype, struct nlattr *nla,
			  const struct nla_policy *policy)
{
	int err;

	err = drbd_nla_check_mandatory(maxtype, nla);
	if (!err)
		err = nla_parse_nested_deprecated(tb, maxtype, nla, policy,
						  NULL);

	return err;
}
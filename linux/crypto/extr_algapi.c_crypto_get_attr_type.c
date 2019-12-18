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
struct rtattr {scalar_t__ rta_type; } ;
struct crypto_attr_type {int dummy; } ;

/* Variables and functions */
 scalar_t__ CRYPTOA_TYPE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 struct crypto_attr_type* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct crypto_attr_type* RTA_DATA (struct rtattr*) ; 
 int RTA_PAYLOAD (struct rtattr*) ; 

struct crypto_attr_type *crypto_get_attr_type(struct rtattr **tb)
{
	struct rtattr *rta = tb[0];
	struct crypto_attr_type *algt;

	if (!rta)
		return ERR_PTR(-ENOENT);
	if (RTA_PAYLOAD(rta) < sizeof(*algt))
		return ERR_PTR(-EINVAL);
	if (rta->rta_type != CRYPTOA_TYPE)
		return ERR_PTR(-EINVAL);

	algt = RTA_DATA(rta);

	return algt;
}
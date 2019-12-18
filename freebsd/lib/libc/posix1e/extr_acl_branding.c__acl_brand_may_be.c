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
typedef  int /*<<< orphan*/  acl_t ;

/* Variables and functions */
 int ACL_BRAND_UNKNOWN ; 
 int _acl_brand (int /*<<< orphan*/  const) ; 

int
_acl_brand_may_be(const acl_t acl, int brand)
{

	if (_acl_brand(acl) == ACL_BRAND_UNKNOWN)
		return (1);

	if (_acl_brand(acl) == brand)
		return (1);

	return (0);
}
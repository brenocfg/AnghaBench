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
typedef  int /*<<< orphan*/  acl_entry_t ;

/* Variables and functions */
 int _acl_brand_may_be (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  entry2acl (int /*<<< orphan*/  const) ; 

int
_entry_brand_may_be(const acl_entry_t entry, int brand)
{

	return (_acl_brand_may_be(entry2acl(entry), brand));
}
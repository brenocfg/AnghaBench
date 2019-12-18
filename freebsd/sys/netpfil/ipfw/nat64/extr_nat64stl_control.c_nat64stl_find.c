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
typedef  int /*<<< orphan*/  uint8_t ;
struct nat64stl_cfg {int dummy; } ;
struct namedobj_instance {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPFW_TLV_NAT64STL_NAME ; 
 scalar_t__ ipfw_objhash_lookup_name_type (struct namedobj_instance*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct nat64stl_cfg *
nat64stl_find(struct namedobj_instance *ni, const char *name, uint8_t set)
{
	struct nat64stl_cfg *cfg;

	cfg = (struct nat64stl_cfg *)ipfw_objhash_lookup_name_type(ni, set,
	    IPFW_TLV_NAT64STL_NAME, name);

	return (cfg);
}
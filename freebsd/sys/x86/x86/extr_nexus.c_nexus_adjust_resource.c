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
struct rman {int dummy; } ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 struct rman* nexus_rman (int) ; 
 int rman_adjust_resource (struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_is_region_manager (struct resource*,struct rman*) ; 

__attribute__((used)) static int
nexus_adjust_resource(device_t bus, device_t child, int type,
    struct resource *r, rman_res_t start, rman_res_t end)
{
	struct rman *rm;

	rm = nexus_rman(type);
	if (rm == NULL)
		return (ENXIO);
	if (!rman_is_region_manager(r, rm))
		return (EINVAL);
	return (rman_adjust_resource(r, start, end));
}
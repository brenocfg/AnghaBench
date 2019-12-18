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
typedef  int u_int ;
struct resource_list_entry {int /*<<< orphan*/  flags; } ;
struct resource_list {int dummy; } ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int RF_ACTIVE ; 
 int /*<<< orphan*/  RLE_RESERVED ; 
 scalar_t__ device_get_parent (scalar_t__) ; 
 int /*<<< orphan*/  panic (char*) ; 
 struct resource* resource_list_alloc (struct resource_list*,scalar_t__,scalar_t__,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct resource_list_entry* resource_list_find (struct resource_list*,int,int) ; 

struct resource *
resource_list_reserve(struct resource_list *rl, device_t bus, device_t child,
    int type, int *rid, rman_res_t start, rman_res_t end, rman_res_t count, u_int flags)
{
	struct resource_list_entry *rle = NULL;
	int passthrough = (device_get_parent(child) != bus);
	struct resource *r;

	if (passthrough)
		panic(
    "resource_list_reserve() should only be called for direct children");
	if (flags & RF_ACTIVE)
		panic(
    "resource_list_reserve() should only reserve inactive resources");

	r = resource_list_alloc(rl, bus, child, type, rid, start, end, count,
	    flags);
	if (r != NULL) {
		rle = resource_list_find(rl, type, *rid);
		rle->flags |= RLE_RESERVED;
	}
	return (r);
}
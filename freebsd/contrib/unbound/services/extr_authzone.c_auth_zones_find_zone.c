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
typedef  int /*<<< orphan*/  uint16_t ;
struct auth_zones {int dummy; } ;
struct auth_zone {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct auth_zone* auth_zone_find (struct auth_zones*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ auth_zone_find_less_equal (struct auth_zones*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,struct auth_zone**) ; 
 int /*<<< orphan*/  dname_count_size_labels (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/ * dname_get_shared_topdomain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ dname_is_root (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dname_remove_label (int /*<<< orphan*/ **,size_t*) ; 

struct auth_zone*
auth_zones_find_zone(struct auth_zones* az, uint8_t* name, size_t name_len,
	uint16_t dclass)
{
	uint8_t* nm = name;
	size_t nmlen = name_len;
	struct auth_zone* z;
	if(auth_zone_find_less_equal(az, nm, nmlen, dclass, &z)) {
		/* exact match */
		return z;
	} else {
		/* less-or-nothing */
		if(!z) return NULL; /* nothing smaller, nothing above it */
		/* we found smaller name; smaller may be above the name,
		 * but not below it. */
		nm = dname_get_shared_topdomain(z->name, name);
		dname_count_size_labels(nm, &nmlen);
		z = NULL;
	}

	/* search up */
	while(!z) {
		z = auth_zone_find(az, nm, nmlen, dclass);
		if(z) return z;
		if(dname_is_root(nm)) break;
		dname_remove_label(&nm, &nmlen);
	}
	return NULL;
}
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
struct local_zones {int dummy; } ;
struct local_zone {int dummy; } ;

/* Variables and functions */
 struct local_zone* local_zones_tags_lookup (struct local_zones*,int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

struct local_zone* 
local_zones_lookup(struct local_zones* zones,
        uint8_t* name, size_t len, int labs, uint16_t dclass, uint16_t dtype)
{
	return local_zones_tags_lookup(zones, name, len, labs,
		dclass, dtype, NULL, 0, 1);
}
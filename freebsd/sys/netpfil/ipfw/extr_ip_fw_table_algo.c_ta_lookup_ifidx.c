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
typedef  int /*<<< orphan*/  uint32_t ;
struct table_info {int dummy; } ;
struct ifidx {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 struct ifidx* ifidx_find (struct table_info*,void*) ; 

__attribute__((used)) static int
ta_lookup_ifidx(struct table_info *ti, void *key, uint32_t keylen,
    uint32_t *val)
{
	struct ifidx *ifi;

	ifi = ifidx_find(ti, key);

	if (ifi != NULL) {
		*val = ifi->value;
		return (1);
	}

	return (0);
}
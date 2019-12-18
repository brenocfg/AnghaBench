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
typedef  int uint32_t ;
struct kv_name {int key; char const* name; } ;
typedef  int /*<<< orphan*/  bad ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

const char *
kv_lookup(const struct kv_name *kv, size_t kv_count, uint32_t key)
{
	static char bad[32];
	size_t i;

	for (i = 0; i < kv_count; i++, kv++)
		if (kv->key == key)
			return kv->name;
	snprintf(bad, sizeof(bad), "Attribute %#x", key);
	return bad;
}
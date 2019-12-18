#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct object_id {int dummy; } ;
struct TYPE_2__ {int hexsz; } ;

/* Variables and functions */
 int get_oid_hex (char const*,struct object_id*) ; 
 TYPE_1__* the_hash_algo ; 

int parse_oid_hex(const char *hex, struct object_id *oid, const char **end)
{
	int ret = get_oid_hex(hex, oid);
	if (!ret)
		*end = hex + the_hash_algo->hexsz;
	return ret;
}
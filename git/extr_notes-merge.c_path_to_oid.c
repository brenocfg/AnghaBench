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
 int GIT_MAX_HEXSZ ; 
 int get_oid_hex (char*,struct object_id*) ; 
 TYPE_1__* the_hash_algo ; 

__attribute__((used)) static int path_to_oid(const char *path, struct object_id *oid)
{
	char hex_oid[GIT_MAX_HEXSZ];
	int i = 0;
	while (*path && i < the_hash_algo->hexsz) {
		if (*path != '/')
			hex_oid[i++] = *path;
		path++;
	}
	if (*path || i != the_hash_algo->hexsz)
		return -1;
	return get_oid_hex(hex_oid, oid);
}
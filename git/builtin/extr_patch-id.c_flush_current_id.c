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
struct TYPE_2__ {scalar_t__ hexsz; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_MAX_HEXSZ ; 
 int /*<<< orphan*/  memcpy (char*,char*,scalar_t__) ; 
 char* oid_to_hex (struct object_id*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 TYPE_1__* the_hash_algo ; 

__attribute__((used)) static void flush_current_id(int patchlen, struct object_id *id, struct object_id *result)
{
	char name[GIT_MAX_HEXSZ + 1];

	if (!patchlen)
		return;

	memcpy(name, oid_to_hex(id), the_hash_algo->hexsz + 1);
	printf("%s %s\n", oid_to_hex(result), name);
}
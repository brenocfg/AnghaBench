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
struct object_id {int dummy; } ;

/* Variables and functions */
 scalar_t__ GIT_SHA1_HEXSZ ; 
 int /*<<< orphan*/  memcpy (char*,char*,scalar_t__) ; 
 char* oid_to_hex (struct object_id*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 

__attribute__((used)) static void flush_current_id(int patchlen, struct object_id *id, struct object_id *result)
{
	char name[50];

	if (!patchlen)
		return;

	memcpy(name, oid_to_hex(id), GIT_SHA1_HEXSZ + 1);
	printf("%s %s\n", oid_to_hex(result), name);
}
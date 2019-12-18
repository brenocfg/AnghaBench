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
struct pattern_list {int dummy; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_patterns_from_buffer (char*,size_t,char const*,int,struct pattern_list*) ; 
 int do_read_blob (struct object_id*,int /*<<< orphan*/ *,size_t*,char**) ; 

int add_patterns_from_blob_to_list(
	struct object_id *oid,
	const char *base, int baselen,
	struct pattern_list *pl)
{
	char *buf;
	size_t size;
	int r;

	r = do_read_blob(oid, NULL, &size, &buf);
	if (r != 1)
		return r;

	add_patterns_from_buffer(buf, size, base, baselen, pl);
	return 0;
}
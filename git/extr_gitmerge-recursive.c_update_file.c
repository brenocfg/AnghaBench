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
struct merge_options {scalar_t__ call_depth; } ;

/* Variables and functions */
 int update_file_flags (struct merge_options*,struct object_id const*,unsigned int,char const*,int,int) ; 

__attribute__((used)) static int update_file(struct merge_options *o,
		       int clean,
		       const struct object_id *oid,
		       unsigned mode,
		       const char *path)
{
	return update_file_flags(o, oid, mode, path, o->call_depth || clean, !o->call_depth);
}
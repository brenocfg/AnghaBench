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
struct traverse_info {int dummy; } ;
struct name_entry {int dummy; } ;
struct TYPE_2__ {scalar_t__ rawsz; } ;

/* Variables and functions */
 char* make_traverse_path (char*,struct traverse_info const*,struct name_entry const*) ; 
 TYPE_1__* the_hash_algo ; 
 scalar_t__ traverse_path_len (struct traverse_info const*,struct name_entry const*) ; 
 char* xmallocz (scalar_t__) ; 

__attribute__((used)) static char *traverse_path(const struct traverse_info *info, const struct name_entry *n)
{
	char *path = xmallocz(traverse_path_len(info, n) + the_hash_algo->rawsz);
	return make_traverse_path(path, info, n);
}
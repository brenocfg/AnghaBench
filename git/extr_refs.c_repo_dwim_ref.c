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
struct repository {int dummy; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int expand_ref (struct repository*,char const*,int,struct object_id*,char**) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* substitute_branch_name (struct repository*,char const**,int*) ; 

int repo_dwim_ref(struct repository *r, const char *str, int len,
		  struct object_id *oid, char **ref)
{
	char *last_branch = substitute_branch_name(r, &str, &len);
	int   refs_found  = expand_ref(r, str, len, oid, ref);
	free(last_branch);
	return refs_found;
}
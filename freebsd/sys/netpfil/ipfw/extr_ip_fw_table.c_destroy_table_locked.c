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
struct table_config {int dummy; } ;
struct namedobj_instance {int dummy; } ;
struct named_object {int kidx; char* name; } ;
struct ip_fw_chain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_table_config (struct namedobj_instance*,struct table_config*) ; 
 scalar_t__ ipfw_objhash_free_idx (struct namedobj_instance*,int) ; 
 int /*<<< orphan*/  printf (char*,int,char*) ; 
 int /*<<< orphan*/  unlink_table (struct ip_fw_chain*,struct table_config*) ; 

__attribute__((used)) static int
destroy_table_locked(struct namedobj_instance *ni, struct named_object *no,
    void *arg)
{

	unlink_table((struct ip_fw_chain *)arg, (struct table_config *)no);
	if (ipfw_objhash_free_idx(ni, no->kidx) != 0)
		printf("Error unlinking kidx %d from table %s\n",
		    no->kidx, no->name);
	free_table_config(ni, (struct table_config *)no);
	return (0);
}
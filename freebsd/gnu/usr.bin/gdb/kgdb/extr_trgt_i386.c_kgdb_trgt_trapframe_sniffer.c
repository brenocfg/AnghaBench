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
struct frame_unwind {int dummy; } ;
struct frame_info {int dummy; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ PMAP_TRM_MIN_ADDRESS ; 
 int /*<<< orphan*/  find_pc_partial_function (scalar_t__,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ frame_pc_unwind (struct frame_info*) ; 
 struct frame_unwind const kgdb_trgt_dblfault_unwind ; 
 struct frame_unwind const kgdb_trgt_trapframe_unwind ; 
 scalar_t__ strcmp (char*,char*) ; 

const struct frame_unwind *
kgdb_trgt_trapframe_sniffer(struct frame_info *next_frame)
{
	char *pname;
	CORE_ADDR pc;

	pc = frame_pc_unwind(next_frame);
	if (pc >= PMAP_TRM_MIN_ADDRESS)
		return (&kgdb_trgt_trapframe_unwind);
	pname = NULL;
	find_pc_partial_function(pc, &pname, NULL, NULL);
	if (pname == NULL)
		return (NULL);
	if (strcmp(pname, "dblfault_handler") == 0)
		return (&kgdb_trgt_dblfault_unwind);
	if (strcmp(pname, "calltrap") == 0 ||
	    (pname[0] == 'X' && pname[1] != '_'))
		return (&kgdb_trgt_trapframe_unwind);
	/* printf("%s: %llx =%s\n", __func__, pc, pname); */
	return (NULL);
}
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
struct objfile {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kgdb_new_objfile_chain (struct objfile*) ; 
 int /*<<< orphan*/  kgdb_trgt_new_objfile (struct objfile*) ; 
 int /*<<< orphan*/  kld_new_objfile (struct objfile*) ; 
 int /*<<< orphan*/  push_remote_target (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * remote ; 
 struct objfile* symfile_objfile ; 

__attribute__((used)) static void
kgdb_new_objfile(struct objfile *objfile)
{
	static int once = 1;

	kld_new_objfile(objfile);
	kgdb_trgt_new_objfile(objfile);

	if (kgdb_new_objfile_chain != NULL)
		kgdb_new_objfile_chain(objfile);

	if (once && objfile != NULL && objfile == symfile_objfile) {
		/*
		 * The initial kernel has just been loaded.  Start the
		 * remote target if we have one.
		 */
		once = 0;
		if (remote != NULL)
			push_remote_target (remote, 0);
	}
}
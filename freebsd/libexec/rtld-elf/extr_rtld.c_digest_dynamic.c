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
typedef  int /*<<< orphan*/  Obj_Entry ;
typedef  int /*<<< orphan*/  Elf_Dyn ;

/* Variables and functions */
 int /*<<< orphan*/  digest_dynamic1 (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  digest_dynamic2 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
digest_dynamic(Obj_Entry *obj, int early)
{
	const Elf_Dyn *dyn_rpath;
	const Elf_Dyn *dyn_soname;
	const Elf_Dyn *dyn_runpath;

	digest_dynamic1(obj, early, &dyn_rpath, &dyn_soname, &dyn_runpath);
	digest_dynamic2(obj, dyn_rpath, dyn_soname, dyn_runpath);
}
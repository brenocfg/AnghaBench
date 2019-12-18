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
struct TYPE_2__ {int /*<<< orphan*/  bi_esymtab; int /*<<< orphan*/  bi_symtab; } ;

/* Variables and functions */
 int /*<<< orphan*/  KDB_WHY_BOOTFLAGS ; 
 int RB_KDB ; 
 int boothowto ; 
 TYPE_1__ bootinfo ; 
 int /*<<< orphan*/  db_fetch_ksymtab (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kdb_enter (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kdb_init () ; 

__attribute__((used)) static void
i386_kdb_init(void)
{
#ifdef DDB
	db_fetch_ksymtab(bootinfo.bi_symtab, bootinfo.bi_esymtab);
#endif
	kdb_init();
#ifdef KDB
	if (boothowto & RB_KDB)
		kdb_enter(KDB_WHY_BOOTFLAGS, "Boot flags requested debugger");
#endif
}
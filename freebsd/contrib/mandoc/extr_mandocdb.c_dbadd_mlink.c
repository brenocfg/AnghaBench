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
struct mlink {int /*<<< orphan*/  file; TYPE_1__* mpage; int /*<<< orphan*/  arch; int /*<<< orphan*/  fsec; int /*<<< orphan*/  dsec; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  dba; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBP_ARCH ; 
 int /*<<< orphan*/  DBP_FILE ; 
 int /*<<< orphan*/  DBP_SECT ; 
 int /*<<< orphan*/  NAME_FILE ; 
 int /*<<< orphan*/  dba_page_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dba_page_alias (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dbadd_mlink(const struct mlink *mlink)
{
	dba_page_alias(mlink->mpage->dba, mlink->name, NAME_FILE);
	dba_page_add(mlink->mpage->dba, DBP_SECT, mlink->dsec);
	dba_page_add(mlink->mpage->dba, DBP_SECT, mlink->fsec);
	dba_page_add(mlink->mpage->dba, DBP_ARCH, mlink->arch);
	dba_page_add(mlink->mpage->dba, DBP_FILE, mlink->file);
}
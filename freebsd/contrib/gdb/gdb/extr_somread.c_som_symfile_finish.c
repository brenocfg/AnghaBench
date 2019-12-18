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
struct objfile {int /*<<< orphan*/ * sym_stab_info; int /*<<< orphan*/  md; } ;

/* Variables and functions */
 int /*<<< orphan*/  hpread_symfile_finish (struct objfile*) ; 
 int /*<<< orphan*/  xmfree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
som_symfile_finish (struct objfile *objfile)
{
  if (objfile->sym_stab_info != NULL)
    {
      xmfree (objfile->md, objfile->sym_stab_info);
    }
  hpread_symfile_finish (objfile);
}
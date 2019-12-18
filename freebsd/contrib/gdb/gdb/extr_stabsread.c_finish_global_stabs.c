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
 int /*<<< orphan*/ * global_stabs ; 
 int /*<<< orphan*/  global_symbols ; 
 int /*<<< orphan*/  patch_block_stabs (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct objfile*) ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ *) ; 

void
finish_global_stabs (struct objfile *objfile)
{
  if (global_stabs)
    {
      patch_block_stabs (global_symbols, global_stabs, objfile);
      xfree (global_stabs);
      global_stabs = NULL;
    }
}
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
struct mrb_dir {int /*<<< orphan*/ * dir; } ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_free (int /*<<< orphan*/ *,struct mrb_dir*) ; 

void
mrb_dir_free(mrb_state *mrb, void *ptr)
{
  struct mrb_dir *mdir = (struct mrb_dir *)ptr;

  if (mdir->dir) {
    closedir(mdir->dir);
    mdir->dir = NULL;
  }
  mrb_free(mrb, mdir);
}
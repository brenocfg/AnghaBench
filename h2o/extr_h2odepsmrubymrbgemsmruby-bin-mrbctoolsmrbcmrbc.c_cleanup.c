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
struct mrbc_args {scalar_t__ outfile; } ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  mrb_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_free (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static void
cleanup(mrb_state *mrb, struct mrbc_args *args)
{
  mrb_free(mrb, (void*)args->outfile);
  mrb_close(mrb);
}
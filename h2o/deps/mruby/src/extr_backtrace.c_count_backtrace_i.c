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
struct backtrace_location {int /*<<< orphan*/ * filename; } ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */

__attribute__((used)) static void
count_backtrace_i(mrb_state *mrb,
                 struct backtrace_location *loc,
                 void *data)
{
  int *lenp = (int*)data;

  if (loc->filename == NULL) return;
  (*lenp)++;
}
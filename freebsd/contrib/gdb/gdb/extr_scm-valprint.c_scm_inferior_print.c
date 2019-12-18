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
struct ui_file {int dummy; } ;
typedef  enum val_prettyprint { ____Placeholder_val_prettyprint } val_prettyprint ;
typedef  int /*<<< orphan*/  LONGEST ;

/* Variables and functions */

__attribute__((used)) static int
scm_inferior_print (LONGEST value, struct ui_file *stream, int format,
		    int deref_ref, int recurse, enum val_prettyprint pretty)
{
  return -1;
}
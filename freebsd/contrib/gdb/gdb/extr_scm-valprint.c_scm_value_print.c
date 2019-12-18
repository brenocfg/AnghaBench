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
struct value {int dummy; } ;
struct ui_file {int dummy; } ;
typedef  enum val_prettyprint { ____Placeholder_val_prettyprint } val_prettyprint ;

/* Variables and functions */
 int common_val_print (struct value*,struct ui_file*,int,int,int /*<<< orphan*/ ,int) ; 

int
scm_value_print (struct value *val, struct ui_file *stream, int format,
		 enum val_prettyprint pretty)
{
  return (common_val_print (val, stream, format, 1, 0, pretty));
}
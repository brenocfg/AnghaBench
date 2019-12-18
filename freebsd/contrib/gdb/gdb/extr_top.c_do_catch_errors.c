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
struct ui_out {int dummy; } ;
struct catch_errors_args {int (* func ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  func_args; } ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
do_catch_errors (struct ui_out *uiout, void *data)
{
  struct catch_errors_args *args = data;
  return args->func (args->func_args);
}
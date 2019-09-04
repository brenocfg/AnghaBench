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
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t_printstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

mrb_value
mrb_t_printstr(mrb_state *mrb, mrb_value self)
{
  mrb_value argv;

  mrb_get_args(mrb, "o", &argv);
  t_printstr(mrb, argv);

  return argv;
}
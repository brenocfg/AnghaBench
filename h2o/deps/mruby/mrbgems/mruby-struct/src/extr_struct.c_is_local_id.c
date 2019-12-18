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
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int mrb_bool ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  ISUPPER (char const) ; 

__attribute__((used)) static mrb_bool
is_local_id(mrb_state *mrb, const char *name)
{
  if (!name) return FALSE;
  return !ISUPPER(name[0]);
}
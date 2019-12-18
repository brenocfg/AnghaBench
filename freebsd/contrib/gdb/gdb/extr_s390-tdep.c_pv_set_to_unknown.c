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
struct prologue_value {int /*<<< orphan*/  kind; } ;

/* Variables and functions */
 int /*<<< orphan*/  pv_unknown ; 

__attribute__((used)) static void
pv_set_to_unknown (struct prologue_value *v)
{
  v->kind = pv_unknown;
}
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
typedef  int /*<<< orphan*/  LONGEST ;

/* Variables and functions */
 int /*<<< orphan*/  builtin_type_int ; 
 int /*<<< orphan*/  lookup_internalvar (char*) ; 
 int /*<<< orphan*/  set_internalvar (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tracepoint_count ; 
 int /*<<< orphan*/  value_from_longest (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_tracepoint_count (int num)
{
  tracepoint_count = num;
  set_internalvar (lookup_internalvar ("tpnum"),
		   value_from_longest (builtin_type_int, (LONGEST) num));
}
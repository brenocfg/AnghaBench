#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct TYPE_2__ {int use; } ;

/* Variables and functions */
 TYPE_1__* handles ; 
 scalar_t__ num_handles ; 

__attribute__((used)) static int
handle_is_ok(int i, int type)
{
	return i >= 0 && (u_int)i < num_handles && handles[i].use == type;
}
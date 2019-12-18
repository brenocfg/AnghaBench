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
struct TYPE_2__ {int next_unused; int /*<<< orphan*/  use; } ;

/* Variables and functions */
 int /*<<< orphan*/  HANDLE_UNUSED ; 
 int first_unused_handle ; 
 TYPE_1__* handles ; 

__attribute__((used)) static void handle_unused(int i)
{
	handles[i].use = HANDLE_UNUSED;
	handles[i].next_unused = first_unused_handle;
	first_unused_handle = i;
}
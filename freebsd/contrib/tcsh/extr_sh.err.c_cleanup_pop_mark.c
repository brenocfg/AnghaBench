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

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 size_t cleanup_mark ; 
 size_t cleanup_sp ; 

void
cleanup_pop_mark(size_t mark)
{
    assert (mark <= cleanup_sp);
    cleanup_mark = mark;
}
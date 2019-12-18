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
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  LINENUM ;

/* Variables and functions */
 int /*<<< orphan*/  p_base ; 
 int /*<<< orphan*/  p_bline ; 

__attribute__((used)) static void
next_intuit_at(off_t file_pos, LINENUM file_line)
{
	p_base = file_pos;
	p_bline = file_line;
}
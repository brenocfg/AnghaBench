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
 int /*<<< orphan*/  INDENT ; 
 int /*<<< orphan*/  column ; 
 int /*<<< orphan*/  oldcol ; 
 int /*<<< orphan*/  outbuf ; 
 int /*<<< orphan*/  strcpy_DYN (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trailer ; 
 int /*<<< orphan*/  trim_trailing () ; 

__attribute__((used)) static void
force_wrap(void)
{
    oldcol = column;
    trim_trailing();
    strcpy_DYN(&outbuf, trailer);
    column = INDENT;
}
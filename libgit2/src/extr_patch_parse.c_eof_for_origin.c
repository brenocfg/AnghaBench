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
 int GIT_DIFF_LINE_ADDITION ; 
 int GIT_DIFF_LINE_ADD_EOFNL ; 
 int GIT_DIFF_LINE_CONTEXT_EOFNL ; 
 int GIT_DIFF_LINE_DELETION ; 
 int GIT_DIFF_LINE_DEL_EOFNL ; 

__attribute__((used)) static int eof_for_origin(int origin) {
	if (origin == GIT_DIFF_LINE_ADDITION)
		return GIT_DIFF_LINE_ADD_EOFNL;
	if (origin == GIT_DIFF_LINE_DELETION)
		return GIT_DIFF_LINE_DEL_EOFNL;
	return GIT_DIFF_LINE_CONTEXT_EOFNL;
}
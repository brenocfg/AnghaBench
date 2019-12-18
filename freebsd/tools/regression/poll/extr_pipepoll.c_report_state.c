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
 scalar_t__ FT_PIPE ; 
 scalar_t__ FT_SOCKETPAIR ; 
 scalar_t__ filetype ; 
 int /*<<< orphan*/  printf (char*,char*,char const*) ; 

__attribute__((used)) static void
report_state(const char *state)
{

	printf(" %s state %s: ",
	    filetype == FT_PIPE ? "Pipe" :
	    filetype == FT_SOCKETPAIR ? "Sock" : "FIFO",
	    state);
}
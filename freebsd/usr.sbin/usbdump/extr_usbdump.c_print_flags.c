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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXT_BUFFER ; 
 char* FLAGS (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FORCE_SHORT_XFER ; 
 int /*<<< orphan*/  MANUAL_STATUS ; 
 int /*<<< orphan*/  NO_PIPE_OK ; 
 int /*<<< orphan*/  PIPE_BOF ; 
 int /*<<< orphan*/  PROXY_BUFFER ; 
 int /*<<< orphan*/  SHORT_FRAMES_OK ; 
 int /*<<< orphan*/  SHORT_XFER_OK ; 
 int /*<<< orphan*/  STALL_PIPE ; 
 int /*<<< orphan*/  printf (char*,int,char*,char*,char*,char*,char*,char*,char*,char*,char*) ; 

__attribute__((used)) static void
print_flags(uint32_t flags)
{
	printf(" flags %#x <%s%s%s%s%s%s%s%s%s0>\n",
	    flags,
	    FLAGS(flags, FORCE_SHORT_XFER),
	    FLAGS(flags, SHORT_XFER_OK),
	    FLAGS(flags, SHORT_FRAMES_OK),
	    FLAGS(flags, PIPE_BOF),
	    FLAGS(flags, PROXY_BUFFER),
	    FLAGS(flags, EXT_BUFFER),
	    FLAGS(flags, MANUAL_STATUS),
	    FLAGS(flags, NO_PIPE_OK),
	    FLAGS(flags, STALL_PIPE));
}
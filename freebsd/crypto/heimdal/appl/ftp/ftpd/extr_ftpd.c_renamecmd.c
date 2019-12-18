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
 int /*<<< orphan*/  LOGCMD2 (char*,char*,char*) ; 
 int /*<<< orphan*/  ack (char*) ; 
 scalar_t__ filename_check (char*) ; 
 scalar_t__ guest ; 
 int /*<<< orphan*/  perror_reply (int,char*) ; 
 scalar_t__ rename (char*,char*) ; 

void
renamecmd(char *from, char *to)
{

	LOGCMD2("rename", from, to);
	if(guest && filename_check(to))
	    return;
	if (rename(from, to) < 0)
		perror_reply(550, "rename");
	else
		ack("RNTO");
}
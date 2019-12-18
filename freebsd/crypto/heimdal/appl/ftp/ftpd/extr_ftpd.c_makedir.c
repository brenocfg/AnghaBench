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
 int /*<<< orphan*/  LOGCMD (char*,char*) ; 
 int /*<<< orphan*/  chmod (char*,int) ; 
 scalar_t__ filename_check (char*) ; 
 scalar_t__ guest ; 
 scalar_t__ mkdir (char*,int) ; 
 int /*<<< orphan*/  perror_reply (int,char*) ; 
 int /*<<< orphan*/  reply (int,char*) ; 

void
makedir(char *name)
{

	LOGCMD("mkdir", name);
	if(guest && filename_check(name))
	    return;
	if (mkdir(name, 0777) < 0)
		perror_reply(550, name);
	else{
	    if(guest)
		chmod(name, 0700); /* guest has umask 777 */
	    reply(257, "MKD command successful.");
	}
}
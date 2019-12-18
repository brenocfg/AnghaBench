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
typedef  int /*<<< orphan*/  path ;

/* Variables and functions */
 int MaxPathLen ; 
 int /*<<< orphan*/  errno ; 
 char* getcwd (char*,int) ; 
 int /*<<< orphan*/  reply (int,char*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

void
pwd(void)
{
    char path[MaxPathLen];
    char *ret;

    /* SunOS has a broken getcwd that does popen(pwd) (!!!), this
     * failes miserably when running chroot
     */
    ret = getcwd(path, sizeof(path));
    if (ret == NULL)
	reply(550, "%s.", strerror(errno));
    else
	reply(257, "\"%s\" is current directory.", path);
}
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
typedef  int ng_ID_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGM_GENERIC_COOKIE ; 
 int /*<<< orphan*/  NGM_SHUTDOWN ; 
 int NG_PATHSIZ ; 
 int NgSendMsg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csock ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

int
ng_shutdown_id(ng_ID_t id)
{
	char path[NG_PATHSIZ];

	snprintf(path, NG_PATHSIZ, "[%x]:", id);
	return (NgSendMsg(csock, path, NGM_GENERIC_COOKIE,
	    NGM_SHUTDOWN, NULL, 0));
}
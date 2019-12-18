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
struct ngm_rmhook {int /*<<< orphan*/  ourhook; } ;
typedef  int /*<<< orphan*/  rmhook ;
typedef  int ng_ID_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGM_GENERIC_COOKIE ; 
 int /*<<< orphan*/  NGM_RMHOOK ; 
 int /*<<< orphan*/  NG_HOOKSIZ ; 
 int NG_PATHSIZ ; 
 int NgSendMsg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ngm_rmhook*,int) ; 
 int /*<<< orphan*/  csock ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

int
ng_rmhook_id(ng_ID_t id, const char *hook)
{
	struct ngm_rmhook rmhook;
	char path[NG_PATHSIZ];

	strlcpy(rmhook.ourhook, hook, NG_HOOKSIZ);
	snprintf(path, NG_PATHSIZ, "[%x]:", id);
	return (NgSendMsg(csock, path,
	    NGM_GENERIC_COOKIE, NGM_RMHOOK, &rmhook, sizeof(rmhook)));
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct ng_mesg {scalar_t__ data; } ;
struct linkinfo {int /*<<< orphan*/  ourhook; } ;
struct TYPE_2__ {size_t hooks; } ;
struct hooklist {struct linkinfo* link; TYPE_1__ nodeinfo; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGM_GENERIC_COOKIE ; 
 int /*<<< orphan*/  NGM_LISTHOOKS ; 
 int /*<<< orphan*/  free (struct ng_mesg*) ; 
 struct ng_mesg* ng_dialog_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static int
find_hook(int32_t id, const u_char *hook, size_t hooklen, struct linkinfo *info)
{
	struct ng_mesg *resp;
	struct hooklist *list;
	u_int i;

	if ((resp = ng_dialog_id(id, NGM_GENERIC_COOKIE,
	    NGM_LISTHOOKS, NULL, 0)) == NULL)
		return (-1);

	list = (struct hooklist *)(void *)resp->data;

	for (i = 0; i < list->nodeinfo.hooks; i++) {
		if (strlen(list->link[i].ourhook) == hooklen &&
		    strncmp(list->link[i].ourhook, hook, hooklen) == 0) {
			*info = list->link[i];
			free(resp);
			return (0);
		}
	}
	free(resp);
	return (-1);
}
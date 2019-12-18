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
struct ngm_name {int /*<<< orphan*/  name; int /*<<< orphan*/  peerhook; int /*<<< orphan*/  ourhook; int /*<<< orphan*/  type; } ;
struct ngm_mkpeer {int /*<<< orphan*/  name; int /*<<< orphan*/  peerhook; int /*<<< orphan*/  ourhook; int /*<<< orphan*/  type; } ;
typedef  int ng_ID_t ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  mkpeer ;

/* Variables and functions */
 int /*<<< orphan*/  NGM_GENERIC_COOKIE ; 
 int /*<<< orphan*/  NGM_MKPEER ; 
 int /*<<< orphan*/  NGM_NAME ; 
 int /*<<< orphan*/  NG_HOOKSIZ ; 
 int NG_PATHSIZ ; 
 int /*<<< orphan*/  NG_TYPESIZ ; 
 int NgSendMsg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ngm_name*,int) ; 
 int /*<<< orphan*/  csock ; 
 int ng_next_node_id_internal (int,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

ng_ID_t
ng_mkpeer_id(ng_ID_t id, const char *nodename, const char *type,
    const char *hook, const char *peerhook)
{
	char path[NG_PATHSIZ];
	struct ngm_mkpeer mkpeer;
	struct ngm_name name;

	strlcpy(mkpeer.type, type, NG_TYPESIZ);
	strlcpy(mkpeer.ourhook, hook, NG_HOOKSIZ);
	strlcpy(mkpeer.peerhook, peerhook, NG_HOOKSIZ);

	sprintf(path, "[%x]:", id);
	if (NgSendMsg(csock, path, NGM_GENERIC_COOKIE, NGM_MKPEER,
	    &mkpeer, sizeof(mkpeer)) == -1)
		return (0);

	if ((id = ng_next_node_id_internal(id, NULL, hook, 0)) == 0)
		return (0);

	if (nodename != NULL) {
		strcpy(name.name, nodename);
		sprintf(path, "[%x]:", id);
		if (NgSendMsg(csock, path, NGM_GENERIC_COOKIE, NGM_NAME,
		    &name, sizeof(name)) == -1)
			return (0);
	}
	return (id);
}
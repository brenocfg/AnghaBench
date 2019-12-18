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
typedef  scalar_t__ u_int ;
struct TYPE_2__ {scalar_t__ typecookie; } ;
struct ng_mesg {TYPE_1__ header; } ;
struct msgreg {scalar_t__ cookie; scalar_t__ id; int /*<<< orphan*/  arg; int /*<<< orphan*/  (* func ) (struct ng_mesg*,char const*,scalar_t__,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 struct msgreg* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 struct msgreg* SLIST_NEXT (struct msgreg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ng_mesg*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  msgreg_list ; 
 int sscanf (char const*,char*,scalar_t__*,int*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  stub1 (struct ng_mesg*,char const*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static void
csock_handle(struct ng_mesg *mesg, const char *path)
{
	struct msgreg *d, *d1;
	u_int id;
	int len;

	if (sscanf(path, "[%x]:%n", &id, &len) != 1 ||
	    (u_int)len != strlen(path)) {
		syslog(LOG_ERR, "cannot parse message path '%s'", path);
		id = 0;
	}

	d = SLIST_FIRST(&msgreg_list);
	while (d != NULL) {
		d1 = SLIST_NEXT(d, link);
		if (d->cookie == mesg->header.typecookie &&
		    (d->id == 0 || d->id == id || id == 0))
			(*d->func)(mesg, path, id, d->arg);
		d = d1;
	}
	free(mesg);
}
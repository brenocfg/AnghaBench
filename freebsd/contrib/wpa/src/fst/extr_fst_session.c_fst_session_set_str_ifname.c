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
struct fst_session {int dummy; } ;
struct fst_iface {int dummy; } ;
struct fst_group {int dummy; } ;
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_WARNING ; 
 int /*<<< orphan*/  fst_group_get_id (struct fst_group*) ; 
 struct fst_iface* fst_group_get_iface_by_name (struct fst_group*,char const*) ; 
 int /*<<< orphan*/  fst_printf_session (struct fst_session*,int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 struct fst_group* fst_session_get_group (struct fst_session*) ; 
 int /*<<< orphan*/  fst_session_set_iface (struct fst_session*,struct fst_iface*,int /*<<< orphan*/ ) ; 

int fst_session_set_str_ifname(struct fst_session *s, const char *ifname,
			       Boolean is_old)
{
	struct fst_group *g = fst_session_get_group(s);
	struct fst_iface *i;

	i = fst_group_get_iface_by_name(g, ifname);
	if (!i) {
		fst_printf_session(s, MSG_WARNING,
				   "Cannot set iface %s: no such iface within group '%s'",
				   ifname, fst_group_get_id(g));
		return -1;
	}

	fst_session_set_iface(s, i, is_old);

	return 0;
}
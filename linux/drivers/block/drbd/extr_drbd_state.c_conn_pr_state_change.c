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
typedef  union drbd_state {int dummy; } drbd_state ;
struct drbd_connection {int dummy; } ;
typedef  enum chg_state_flags { ____Placeholder_chg_state_flags } chg_state_flags ;

/* Variables and functions */
 int CS_DC_SUSP ; 
 int /*<<< orphan*/  drbd_info (struct drbd_connection*,char*,char*) ; 
 int is_susp (union drbd_state) ; 
 int /*<<< orphan*/  print_state_change (char*,union drbd_state,union drbd_state,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 

__attribute__((used)) static void conn_pr_state_change(struct drbd_connection *connection, union drbd_state os, union drbd_state ns,
				 enum chg_state_flags flags)
{
	char pb[300];
	char *pbp = pb;

	pbp += print_state_change(pbp, os, ns, flags);

	if (is_susp(ns) != is_susp(os) && flags & CS_DC_SUSP)
		pbp += sprintf(pbp, "susp( %d -> %d ) ",
			       is_susp(os),
			       is_susp(ns));

	if (pbp != pb)
		drbd_info(connection, "%s\n", pb);
}
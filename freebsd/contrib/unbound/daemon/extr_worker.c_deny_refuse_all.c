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
struct worker {int dummy; } ;
struct comm_reply {int dummy; } ;
struct comm_point {int dummy; } ;
typedef  enum acl_access { ____Placeholder_acl_access } acl_access ;

/* Variables and functions */
 int /*<<< orphan*/  acl_deny ; 
 int /*<<< orphan*/  acl_refuse ; 
 int deny_refuse (struct comm_point*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct worker*,struct comm_reply*) ; 

__attribute__((used)) static int
deny_refuse_all(struct comm_point* c, enum acl_access acl,
	struct worker* worker, struct comm_reply* repinfo)
{
	return deny_refuse(c, acl, acl_deny, acl_refuse, worker, repinfo);
}
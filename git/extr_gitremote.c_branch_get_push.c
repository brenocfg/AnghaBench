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
struct strbuf {int dummy; } ;
struct branch {char const* push_tracking_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 char const* branch_get_push_1 (struct branch*,struct strbuf*) ; 
 char const* error_buf (struct strbuf*,int /*<<< orphan*/ ) ; 

const char *branch_get_push(struct branch *branch, struct strbuf *err)
{
	if (!branch)
		return error_buf(err, _("HEAD does not point to a branch"));

	if (!branch->push_tracking_ref)
		branch->push_tracking_ref = branch_get_push_1(branch, err);
	return branch->push_tracking_ref;
}
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
struct remote {int /*<<< orphan*/  name; int /*<<< orphan*/  fetch; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 char* apply_refspecs (int /*<<< orphan*/ *,char const*) ; 
 char const* error_buf (struct strbuf*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *tracking_for_push_dest(struct remote *remote,
					  const char *refname,
					  struct strbuf *err)
{
	char *ret;

	ret = apply_refspecs(&remote->fetch, refname);
	if (!ret)
		return error_buf(err,
				 _("push destination '%s' on remote '%s' has no local tracking branch"),
				 refname, remote->name);
	return ret;
}
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
struct strbuf {int dummy; } ;
struct TYPE_2__ {scalar_t__ nr; } ;
struct remote {scalar_t__ mirror; int /*<<< orphan*/  name; TYPE_1__ push; } ;
struct branch {char* refname; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
#define  PUSH_DEFAULT_CURRENT 133 
#define  PUSH_DEFAULT_MATCHING 132 
#define  PUSH_DEFAULT_NOTHING 131 
#define  PUSH_DEFAULT_SIMPLE 130 
#define  PUSH_DEFAULT_UNSPECIFIED 129 
#define  PUSH_DEFAULT_UPSTREAM 128 
 int /*<<< orphan*/  _ (char*) ; 
 char* apply_refspecs (TYPE_1__*,char*) ; 
 char const* branch_get_upstream (struct branch*,struct strbuf*) ; 
 char const* error_buf (struct strbuf*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int push_default ; 
 int /*<<< orphan*/  pushremote_for_branch (struct branch*,int /*<<< orphan*/ *) ; 
 struct remote* remote_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 char const* tracking_for_push_dest (struct remote*,char*,struct strbuf*) ; 

__attribute__((used)) static const char *branch_get_push_1(struct branch *branch, struct strbuf *err)
{
	struct remote *remote;

	remote = remote_get(pushremote_for_branch(branch, NULL));
	if (!remote)
		return error_buf(err,
				 _("branch '%s' has no remote for pushing"),
				 branch->name);

	if (remote->push.nr) {
		char *dst;
		const char *ret;

		dst = apply_refspecs(&remote->push, branch->refname);
		if (!dst)
			return error_buf(err,
					 _("push refspecs for '%s' do not include '%s'"),
					 remote->name, branch->name);

		ret = tracking_for_push_dest(remote, dst, err);
		free(dst);
		return ret;
	}

	if (remote->mirror)
		return tracking_for_push_dest(remote, branch->refname, err);

	switch (push_default) {
	case PUSH_DEFAULT_NOTHING:
		return error_buf(err, _("push has no destination (push.default is 'nothing')"));

	case PUSH_DEFAULT_MATCHING:
	case PUSH_DEFAULT_CURRENT:
		return tracking_for_push_dest(remote, branch->refname, err);

	case PUSH_DEFAULT_UPSTREAM:
		return branch_get_upstream(branch, err);

	case PUSH_DEFAULT_UNSPECIFIED:
	case PUSH_DEFAULT_SIMPLE:
		{
			const char *up, *cur;

			up = branch_get_upstream(branch, err);
			if (!up)
				return NULL;
			cur = tracking_for_push_dest(remote, branch->refname, err);
			if (!cur)
				return NULL;
			if (strcmp(cur, up))
				return error_buf(err,
						 _("cannot resolve 'simple' push to a single destination"));
			return cur;
		}
	}

	BUG("unhandled push situation");
}
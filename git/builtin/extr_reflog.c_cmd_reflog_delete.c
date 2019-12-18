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
struct object_id {int dummy; } ;
struct TYPE_2__ {int recno; int /*<<< orphan*/  expire_total; } ;
struct expire_reflog_policy_cb {TYPE_1__ cmd; } ;
typedef  int /*<<< orphan*/  cb ;

/* Variables and functions */
 unsigned int EXPIRE_REFLOGS_DRY_RUN ; 
 unsigned int EXPIRE_REFLOGS_REWRITE ; 
 unsigned int EXPIRE_REFLOGS_UPDATE_REF ; 
 unsigned int EXPIRE_REFLOGS_VERBOSE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  approxidate (char const*) ; 
 int /*<<< orphan*/  count_reflog_ent ; 
 int /*<<< orphan*/  dwim_log (char const*,int,struct object_id*,char**) ; 
 int error (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  for_each_reflog_ent (char*,int /*<<< orphan*/ ,struct expire_reflog_policy_cb*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memset (struct expire_reflog_policy_cb*,int /*<<< orphan*/ ,int) ; 
 char* reflog_delete_usage ; 
 int reflog_expire (char*,struct object_id*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct expire_reflog_policy_cb*) ; 
 int /*<<< orphan*/  reflog_expiry_cleanup ; 
 int /*<<< orphan*/  reflog_expiry_prepare ; 
 int /*<<< orphan*/  should_expire_reflog_ent ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 char* strstr (char const*,char*) ; 
 int strtoul (char const*,char**,int) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmd_reflog_delete(int argc, const char **argv, const char *prefix)
{
	struct expire_reflog_policy_cb cb;
	int i, status = 0;
	unsigned int flags = 0;

	memset(&cb, 0, sizeof(cb));

	for (i = 1; i < argc; i++) {
		const char *arg = argv[i];
		if (!strcmp(arg, "--dry-run") || !strcmp(arg, "-n"))
			flags |= EXPIRE_REFLOGS_DRY_RUN;
		else if (!strcmp(arg, "--rewrite"))
			flags |= EXPIRE_REFLOGS_REWRITE;
		else if (!strcmp(arg, "--updateref"))
			flags |= EXPIRE_REFLOGS_UPDATE_REF;
		else if (!strcmp(arg, "--verbose"))
			flags |= EXPIRE_REFLOGS_VERBOSE;
		else if (!strcmp(arg, "--")) {
			i++;
			break;
		}
		else if (arg[0] == '-')
			usage(_(reflog_delete_usage));
		else
			break;
	}

	if (argc - i < 1)
		return error(_("no reflog specified to delete"));

	for ( ; i < argc; i++) {
		const char *spec = strstr(argv[i], "@{");
		struct object_id oid;
		char *ep, *ref;
		int recno;

		if (!spec) {
			status |= error(_("not a reflog: %s"), argv[i]);
			continue;
		}

		if (!dwim_log(argv[i], spec - argv[i], &oid, &ref)) {
			status |= error(_("no reflog for '%s'"), argv[i]);
			continue;
		}

		recno = strtoul(spec + 2, &ep, 10);
		if (*ep == '}') {
			cb.cmd.recno = -recno;
			for_each_reflog_ent(ref, count_reflog_ent, &cb);
		} else {
			cb.cmd.expire_total = approxidate(spec + 2);
			for_each_reflog_ent(ref, count_reflog_ent, &cb);
			cb.cmd.expire_total = 0;
		}

		status |= reflog_expire(ref, &oid, flags,
					reflog_expiry_prepare,
					should_expire_reflog_ent,
					reflog_expiry_cleanup,
					&cb);
		free(ref);
	}
	return status;
}
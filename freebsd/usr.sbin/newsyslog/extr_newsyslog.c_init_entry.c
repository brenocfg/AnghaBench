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
typedef  scalar_t__ uid_t ;
struct conf_entry {char const* pid_cmd_file; int fsize; int numlogs; int trsize; int hours; scalar_t__ def_cfg; int /*<<< orphan*/  sig; int /*<<< orphan*/  compress; scalar_t__ flags; scalar_t__ permissions; int /*<<< orphan*/ * trim_at; scalar_t__ gid; scalar_t__ uid; scalar_t__ rotate; scalar_t__ firstcreate; int /*<<< orphan*/ * r_reason; int /*<<< orphan*/ * log; } ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  COMPRESS_NONE ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  asprintf (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * destdir ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 struct conf_entry* malloc (int) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/ * ptime_init (int /*<<< orphan*/ *) ; 
 void* strdup (char const*) ; 
 int verbose ; 

__attribute__((used)) static struct conf_entry *
init_entry(const char *fname, struct conf_entry *src_entry)
{
	struct conf_entry *tempwork;

	if (verbose > 4)
		printf("\t--> [creating entry for %s]\n", fname);

	tempwork = malloc(sizeof(struct conf_entry));
	if (tempwork == NULL)
		err(1, "malloc of conf_entry for %s", fname);

	if (destdir == NULL || fname[0] != '/')
		tempwork->log = strdup(fname);
	else
		asprintf(&tempwork->log, "%s%s", destdir, fname);
	if (tempwork->log == NULL)
		err(1, "strdup for %s", fname);

	if (src_entry != NULL) {
		tempwork->pid_cmd_file = NULL;
		if (src_entry->pid_cmd_file)
			tempwork->pid_cmd_file = strdup(src_entry->pid_cmd_file);
		tempwork->r_reason = NULL;
		tempwork->firstcreate = 0;
		tempwork->rotate = 0;
		tempwork->fsize = -1;
		tempwork->uid = src_entry->uid;
		tempwork->gid = src_entry->gid;
		tempwork->numlogs = src_entry->numlogs;
		tempwork->trsize = src_entry->trsize;
		tempwork->hours = src_entry->hours;
		tempwork->trim_at = NULL;
		if (src_entry->trim_at != NULL)
			tempwork->trim_at = ptime_init(src_entry->trim_at);
		tempwork->permissions = src_entry->permissions;
		tempwork->flags = src_entry->flags;
		tempwork->compress = src_entry->compress;
		tempwork->sig = src_entry->sig;
		tempwork->def_cfg = src_entry->def_cfg;
	} else {
		/* Initialize as a "do-nothing" entry */
		tempwork->pid_cmd_file = NULL;
		tempwork->r_reason = NULL;
		tempwork->firstcreate = 0;
		tempwork->rotate = 0;
		tempwork->fsize = -1;
		tempwork->uid = (uid_t)-1;
		tempwork->gid = (gid_t)-1;
		tempwork->numlogs = 1;
		tempwork->trsize = -1;
		tempwork->hours = -1;
		tempwork->trim_at = NULL;
		tempwork->permissions = 0;
		tempwork->flags = 0;
		tempwork->compress = COMPRESS_NONE;
		tempwork->sig = SIGHUP;
		tempwork->def_cfg = 0;
	}

	return (tempwork);
}
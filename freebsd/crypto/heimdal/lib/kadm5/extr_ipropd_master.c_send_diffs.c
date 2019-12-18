#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_11__ {scalar_t__ version; int flags; int /*<<< orphan*/  fd; int /*<<< orphan*/  ac; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ slave ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  krb5_storage ;
struct TYPE_12__ {scalar_t__ length; scalar_t__ data; } ;
typedef  TYPE_2__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  enum kadm_ops { ____Placeholder_kadm_ops } kadm_ops ;

/* Variables and functions */
 int /*<<< orphan*/  FOR_YOU ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int SLAVE_F_DEAD ; 
 int /*<<< orphan*/ * kadm5_log_goto_end (int) ; 
 int kadm5_log_previous (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int*,scalar_t__*) ; 
 int krb5_data_alloc (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  krb5_data_free (TYPE_2__*) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,int,char*) ; 
 int /*<<< orphan*/  krb5_storage_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * krb5_storage_from_data (TYPE_2__*) ; 
 int /*<<< orphan*/  krb5_storage_read (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 scalar_t__ krb5_storage_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_store_int32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  krb5_warnx (int /*<<< orphan*/ ,char*,...) ; 
 int krb5_write_priv_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int send_complete (int /*<<< orphan*/ ,TYPE_1__*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  slave_dead (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  slave_seen (TYPE_1__*) ; 

__attribute__((used)) static int
send_diffs (krb5_context context, slave *s, int log_fd,
	    const char *database, uint32_t current_version)
{
    krb5_storage *sp;
    uint32_t ver;
    time_t timestamp;
    enum kadm_ops op;
    uint32_t len;
    off_t right, left;
    krb5_data data;
    int ret = 0;

    if (s->version == current_version) {
	krb5_warnx(context, "slave %s in sync already at version %ld",
		   s->name, (long)s->version);
	return 0;
    }

    if (s->flags & SLAVE_F_DEAD)
	return 0;

    /* if slave is a fresh client, starting over */
    if (s->version == 0) {
	krb5_warnx(context, "sending complete log to fresh slave %s",
		   s->name);
	return send_complete (context, s, database, current_version);
    }

    sp = kadm5_log_goto_end (log_fd);
    right = krb5_storage_seek(sp, 0, SEEK_CUR);
    for (;;) {
	ret = kadm5_log_previous (context, sp, &ver, &timestamp, &op, &len);
	if (ret)
	    krb5_err(context, 1, ret,
		     "send_diffs: failed to find previous entry");
	left = krb5_storage_seek(sp, -16, SEEK_CUR);
	if (ver == s->version)
	    return 0;
	if (ver == s->version + 1)
	    break;
	if (left == 0) {
	    krb5_storage_free(sp);
	    krb5_warnx(context,
		       "slave %s (version %lu) out of sync with master "
		       "(first version in log %lu), sending complete database",
		       s->name, (unsigned long)s->version, (unsigned long)ver);
	    return send_complete (context, s, database, current_version);
	}
    }

    krb5_warnx(context,
	       "syncing slave %s from version %lu to version %lu",
	       s->name, (unsigned long)s->version,
	       (unsigned long)current_version);

    ret = krb5_data_alloc (&data, right - left + 4);
    if (ret) {
	krb5_storage_free(sp);
	krb5_warn (context, ret, "send_diffs: krb5_data_alloc");
	slave_dead(context, s);
	return 1;
    }
    krb5_storage_read (sp, (char *)data.data + 4, data.length - 4);
    krb5_storage_free(sp);

    sp = krb5_storage_from_data (&data);
    if (sp == NULL) {
	krb5_warnx (context, "send_diffs: krb5_storage_from_data");
	slave_dead(context, s);
	return 1;
    }
    krb5_store_int32 (sp, FOR_YOU);
    krb5_storage_free(sp);

    ret = krb5_write_priv_message(context, s->ac, &s->fd, &data);
    krb5_data_free(&data);

    if (ret) {
	krb5_warn (context, ret, "send_diffs: krb5_write_priv_message");
	slave_dead(context, s);
	return 1;
    }
    slave_seen(s);

    s->version = current_version;

    return 0;
}
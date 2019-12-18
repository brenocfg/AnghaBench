#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  time_t ;
struct replay_options {int start_version_integer; int end_version_integer; } ;
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_4__ {int /*<<< orphan*/  context; } ;
typedef  TYPE_1__ kadm5_server_context ;
typedef  enum kadm_ops { ____Placeholder_kadm_ops } kadm_ops ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ kadm5_log_replay (TYPE_1__*,int,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_storage_seek (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
apply_entry(kadm5_server_context *server_context,
	    uint32_t ver,
	    time_t timestamp,
	    enum kadm_ops op,
	    uint32_t len,
	    krb5_storage *sp,
	    void *ctx)
{
    struct replay_options *opt = ctx;
    krb5_error_code ret;

    if((opt->start_version_integer != -1 && ver < (uint32_t)opt->start_version_integer) ||
       (opt->end_version_integer != -1 && ver > (uint32_t)opt->end_version_integer)) {
	/* XXX skip this entry */
	krb5_storage_seek(sp, len, SEEK_CUR);
	return;
    }
    printf ("ver %u... ", ver);
    fflush (stdout);

    ret = kadm5_log_replay (server_context,
			    op, ver, len, sp);
    if (ret)
	krb5_warn (server_context->context, ret, "kadm5_log_replay");

    printf ("done\n");
}
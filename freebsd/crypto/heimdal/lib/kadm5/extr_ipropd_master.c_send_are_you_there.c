#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; int /*<<< orphan*/  fd; int /*<<< orphan*/  ac; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ slave ;
typedef  int /*<<< orphan*/  krb5_storage ;
struct TYPE_7__ {char* data; int length; } ;
typedef  TYPE_2__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  ARE_YOU_THERE ; 
 int SLAVE_F_AYT ; 
 int SLAVE_F_DEAD ; 
 int /*<<< orphan*/  krb5_storage_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * krb5_storage_from_mem (char*,int) ; 
 int /*<<< orphan*/  krb5_store_int32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  krb5_warnx (int /*<<< orphan*/ ,char*,...) ; 
 int krb5_write_priv_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  slave_dead (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int
send_are_you_there (krb5_context context, slave *s)
{
    krb5_storage *sp;
    krb5_data data;
    char buf[4];
    int ret;

    if (s->flags & (SLAVE_F_DEAD|SLAVE_F_AYT))
	return 0;

    krb5_warnx(context, "slave %s missing, sending AYT", s->name);

    s->flags |= SLAVE_F_AYT;

    data.data = buf;
    data.length = 4;

    sp = krb5_storage_from_mem (buf, 4);
    if (sp == NULL) {
	krb5_warnx (context, "are_you_there: krb5_data_alloc");
	slave_dead(context, s);
	return 1;
    }
    krb5_store_int32 (sp, ARE_YOU_THERE);
    krb5_storage_free (sp);

    ret = krb5_write_priv_message(context, s->ac, &s->fd, &data);

    if (ret) {
	krb5_warn (context, ret, "are_you_there: krb5_write_priv_message");
	slave_dead(context, s);
	return 1;
    }

    return 0;
}
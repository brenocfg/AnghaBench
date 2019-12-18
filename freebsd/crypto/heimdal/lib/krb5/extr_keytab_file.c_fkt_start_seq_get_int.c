#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct fkt_data {int /*<<< orphan*/  filename; } ;
struct TYPE_5__ {int /*<<< orphan*/ * sp; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ krb5_kt_cursor ;
typedef  TYPE_2__* krb5_keytab ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int int8_t ;
struct TYPE_6__ {int version; struct fkt_data* data; } ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 scalar_t__ KRB5_KEYTAB_BADVNO ; 
 int /*<<< orphan*/  KRB5_KT_END ; 
 int /*<<< orphan*/  N_ (char*,char*) ; 
 scalar_t__ _krb5_xlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _krb5_xunlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  krb5_clear_error_message (int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_ret_int8 (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  krb5_storage_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * krb5_storage_from_fd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_storage_set_eof_code (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rk_cloexec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  storage_set_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 

__attribute__((used)) static krb5_error_code
fkt_start_seq_get_int(krb5_context context,
		      krb5_keytab id,
		      int flags,
		      int exclusive,
		      krb5_kt_cursor *c)
{
    int8_t pvno, tag;
    krb5_error_code ret;
    struct fkt_data *d = id->data;

    c->fd = open (d->filename, flags);
    if (c->fd < 0) {
	ret = errno;
	krb5_set_error_message(context, ret,
			       N_("keytab %s open failed: %s", ""),
			       d->filename, strerror(ret));
	return ret;
    }
    rk_cloexec(c->fd);
    ret = _krb5_xlock(context, c->fd, exclusive, d->filename);
    if (ret) {
	close(c->fd);
	return ret;
    }
    c->sp = krb5_storage_from_fd(c->fd);
    if (c->sp == NULL) {
	_krb5_xunlock(context, c->fd);
	close(c->fd);
	krb5_set_error_message(context, ENOMEM,
			       N_("malloc: out of memory", ""));
	return ENOMEM;
    }
    krb5_storage_set_eof_code(c->sp, KRB5_KT_END);
    ret = krb5_ret_int8(c->sp, &pvno);
    if(ret) {
	krb5_storage_free(c->sp);
	_krb5_xunlock(context, c->fd);
	close(c->fd);
	krb5_clear_error_message(context);
	return ret;
    }
    if(pvno != 5) {
	krb5_storage_free(c->sp);
	_krb5_xunlock(context, c->fd);
	close(c->fd);
	krb5_clear_error_message (context);
	return KRB5_KEYTAB_BADVNO;
    }
    ret = krb5_ret_int8(c->sp, &tag);
    if (ret) {
	krb5_storage_free(c->sp);
	_krb5_xunlock(context, c->fd);
	close(c->fd);
	krb5_clear_error_message(context);
	return ret;
    }
    id->version = tag;
    storage_set_flags(context, c->sp, id->version);
    return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct fkt_data {int dummy; } ;
typedef  int off_t ;
struct TYPE_7__ {int /*<<< orphan*/  sp; } ;
typedef  TYPE_1__ krb5_kt_cursor ;
struct TYPE_8__ {int vno; int /*<<< orphan*/ * aliases; void* flags; int /*<<< orphan*/  keyblock; void* timestamp; int /*<<< orphan*/  principal; } ;
typedef  TYPE_2__ krb5_keytab_entry ;
typedef  TYPE_3__* krb5_keytab ;
typedef  int krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int int8_t ;
typedef  int int32_t ;
struct TYPE_9__ {struct fkt_data* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int krb5_kt_ret_keyblock (int /*<<< orphan*/ ,struct fkt_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int krb5_kt_ret_principal (int /*<<< orphan*/ ,struct fkt_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int krb5_ret_int32 (int /*<<< orphan*/ ,int*) ; 
 int krb5_ret_int8 (int /*<<< orphan*/ ,int*) ; 
 int krb5_ret_uint32 (int /*<<< orphan*/ ,void**) ; 
 int krb5_storage_seek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static krb5_error_code
fkt_next_entry_int(krb5_context context,
		   krb5_keytab id,
		   krb5_keytab_entry *entry,
		   krb5_kt_cursor *cursor,
		   off_t *start,
		   off_t *end)
{
    struct fkt_data *d = id->data;
    int32_t len;
    int ret;
    int8_t tmp8;
    int32_t tmp32;
    uint32_t utmp32;
    off_t pos, curpos;

    pos = krb5_storage_seek(cursor->sp, 0, SEEK_CUR);
loop:
    ret = krb5_ret_int32(cursor->sp, &len);
    if (ret)
	return ret;
    if(len < 0) {
	pos = krb5_storage_seek(cursor->sp, -len, SEEK_CUR);
	goto loop;
    }
    ret = krb5_kt_ret_principal (context, d, cursor->sp, &entry->principal);
    if (ret)
	goto out;
    ret = krb5_ret_uint32(cursor->sp, &utmp32);
    entry->timestamp = utmp32;
    if (ret)
	goto out;
    ret = krb5_ret_int8(cursor->sp, &tmp8);
    if (ret)
	goto out;
    entry->vno = tmp8;
    ret = krb5_kt_ret_keyblock (context, d, cursor->sp, &entry->keyblock);
    if (ret)
	goto out;
    /* there might be a 32 bit kvno here
     * if it's zero, assume that the 8bit one was right,
     * otherwise trust the new value */
    curpos = krb5_storage_seek(cursor->sp, 0, SEEK_CUR);
    if(len + 4 + pos - curpos >= 4) {
	ret = krb5_ret_int32(cursor->sp, &tmp32);
	if (ret == 0 && tmp32 != 0)
	    entry->vno = tmp32;
    }
    /* there might be a flags field here */
    if(len + 4 + pos - curpos >= 8) {
	ret = krb5_ret_uint32(cursor->sp, &utmp32);
	if (ret == 0)
	    entry->flags = utmp32;
    } else
	entry->flags = 0;

    entry->aliases = NULL;

    if(start) *start = pos;
    if(end) *end = pos + 4 + len;
 out:
    krb5_storage_seek(cursor->sp, pos + 4 + len, SEEK_SET);
    return ret;
}
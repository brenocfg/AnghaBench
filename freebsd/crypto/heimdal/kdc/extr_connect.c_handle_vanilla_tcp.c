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
typedef  int uint32_t ;
struct descr {int len; scalar_t__ buf; } ;
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  int /*<<< orphan*/  krb5_kdc_configuration ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  kdc_log (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  krb5_ret_uint32 (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  krb5_storage_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * krb5_storage_from_mem (scalar_t__,int) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static int
handle_vanilla_tcp (krb5_context context,
		    krb5_kdc_configuration *config,
		    struct descr *d)
{
    krb5_storage *sp;
    uint32_t len;

    sp = krb5_storage_from_mem(d->buf, d->len);
    if (sp == NULL) {
	kdc_log (context, config, 0, "krb5_storage_from_mem failed");
	return -1;
    }
    krb5_ret_uint32(sp, &len);
    krb5_storage_free(sp);
    if(d->len - 4 >= len) {
	memmove(d->buf, d->buf + 4, d->len - 4);
	d->len -= 4;
	return 1;
    }
    return 0;
}
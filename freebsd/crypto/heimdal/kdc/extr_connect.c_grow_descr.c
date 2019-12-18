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
struct descr {size_t size; size_t len; unsigned char* buf; } ;
typedef  int /*<<< orphan*/  krb5_kdc_configuration ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  clear_descr (struct descr*) ; 
 int /*<<< orphan*/  kdc_log (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,unsigned long) ; 
 size_t max (int,size_t) ; 
 scalar_t__ max_request_tcp ; 
 unsigned char* realloc (unsigned char*,scalar_t__) ; 

__attribute__((used)) static int
grow_descr (krb5_context context,
	    krb5_kdc_configuration *config,
	    struct descr *d, size_t n)
{
    if (d->size - d->len < n) {
	unsigned char *tmp;
	size_t grow;

	grow = max(1024, d->len + n);
	if (d->size + grow > max_request_tcp) {
	    kdc_log(context, config, 0, "Request exceeds max request size (%lu bytes).",
		    (unsigned long)d->size + grow);
	    clear_descr(d);
	    return -1;
	}
	tmp = realloc (d->buf, d->size + grow);
	if (tmp == NULL) {
	    kdc_log(context, config, 0, "Failed to re-allocate %lu bytes.",
		    (unsigned long)d->size + grow);
	    clear_descr(d);
	    return -1;
	}
	d->size += grow;
	d->buf = tmp;
    }
    return 0;
}
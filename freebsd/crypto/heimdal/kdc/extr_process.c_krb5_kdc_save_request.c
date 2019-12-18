#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint32_t ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  krb5_storage ;
struct TYPE_5__ {size_t length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_address ;
typedef  int /*<<< orphan*/  a ;
struct TYPE_6__ {unsigned int tv_sec; } ;
typedef  int /*<<< orphan*/  Der_type ;
typedef  int /*<<< orphan*/  Der_class ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned int MAKE_TAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int O_APPEND ; 
 int O_CREAT ; 
 int O_WRONLY ; 
 TYPE_4__ _kdc_now ; 
 int /*<<< orphan*/  close (int) ; 
 int der_get_tag (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int*,int /*<<< orphan*/ *) ; 
 int errno ; 
 int /*<<< orphan*/  krb5_free_address (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int,char*,...) ; 
 int krb5_sockaddr2address (int /*<<< orphan*/ ,struct sockaddr const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_storage_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * krb5_storage_from_fd (int) ; 
 int /*<<< orphan*/  krb5_store_address (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_store_data (int /*<<< orphan*/ *,TYPE_1__) ; 
 int /*<<< orphan*/  krb5_store_uint32 (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int open (char const*,int,int) ; 
 int /*<<< orphan*/  rk_UNCONST (unsigned char const*) ; 

int
krb5_kdc_save_request(krb5_context context,
		      const char *fn,
		      const unsigned char *buf,
		      size_t len,
		      const krb5_data *reply,
		      const struct sockaddr *sa)
{
    krb5_storage *sp;
    krb5_address a;
    int fd, ret;
    uint32_t t;
    krb5_data d;

    memset(&a, 0, sizeof(a));

    d.data = rk_UNCONST(buf);
    d.length = len;
    t = _kdc_now.tv_sec;

    fd = open(fn, O_WRONLY|O_CREAT|O_APPEND, 0600);
    if (fd < 0) {
	int saved_errno = errno;
	krb5_set_error_message(context, saved_errno, "Failed to open: %s", fn);
	return saved_errno;
    }

    sp = krb5_storage_from_fd(fd);
    close(fd);
    if (sp == NULL) {
	krb5_set_error_message(context, ENOMEM, "Storage failed to open fd");
	return ENOMEM;
    }

    ret = krb5_sockaddr2address(context, sa, &a);
    if (ret)
	goto out;

    krb5_store_uint32(sp, 1);
    krb5_store_uint32(sp, t);
    krb5_store_address(sp, a);
    krb5_store_data(sp, d);
    {
	Der_class cl;
	Der_type ty;
	unsigned int tag;
	ret = der_get_tag (reply->data, reply->length,
			   &cl, &ty, &tag, NULL);
	if (ret) {
	    krb5_store_uint32(sp, 0xffffffff);
	    krb5_store_uint32(sp, 0xffffffff);
	} else {
	    krb5_store_uint32(sp, MAKE_TAG(cl, ty, 0));
	    krb5_store_uint32(sp, tag);
	}
    }

    krb5_free_address(context, &a);
out:
    krb5_storage_free(sp);

    return 0;
}
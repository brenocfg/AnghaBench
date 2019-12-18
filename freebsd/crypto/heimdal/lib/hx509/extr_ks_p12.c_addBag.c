#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  heim_oid ;
struct TYPE_7__ {size_t length; void* data; } ;
struct TYPE_6__ {TYPE_3__* content; int /*<<< orphan*/  contentType; } ;
struct TYPE_5__ {int len; TYPE_2__* val; } ;
typedef  TYPE_1__ PKCS12_AuthenticatedSafe ;

/* Variables and functions */
 int ENOMEM ; 
 TYPE_3__* calloc (int,int) ; 
 int der_copy_oid (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  der_free_oid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 void* realloc (TYPE_2__*,int) ; 

__attribute__((used)) static int
addBag(hx509_context context,
       PKCS12_AuthenticatedSafe *as,
       const heim_oid *oid,
       void *data,
       size_t length)
{
    void *ptr;
    int ret;

    ptr = realloc(as->val, sizeof(as->val[0]) * (as->len + 1));
    if (ptr == NULL) {
	hx509_set_error_string(context, 0, ENOMEM, "out of memory");
	return ENOMEM;
    }
    as->val = ptr;

    ret = der_copy_oid(oid, &as->val[as->len].contentType);
    if (ret) {
	hx509_set_error_string(context, 0, ret, "out of memory");
	return ret;
    }

    as->val[as->len].content = calloc(1, sizeof(*as->val[0].content));
    if (as->val[as->len].content == NULL) {
	der_free_oid(&as->val[as->len].contentType);
	hx509_set_error_string(context, 0, ENOMEM, "malloc out of memory");
	return ENOMEM;
    }

    as->val[as->len].content->data = data;
    as->val[as->len].content->length = length;

    as->len++;

    return 0;
}
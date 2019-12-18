#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long len; int /*<<< orphan*/ * val; } ;
struct mem_data {TYPE_1__ certs; } ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_certs ;
typedef  int /*<<< orphan*/ * hx509_cert ;

/* Variables and functions */
 int /*<<< orphan*/ * hx509_cert_ref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mem_iter(hx509_context contexst,
	 hx509_certs certs,
	 void *data,
	 void *cursor,
	 hx509_cert *cert)
{
    unsigned long *iter = cursor;
    struct mem_data *mem = data;

    if (*iter >= mem->certs.len) {
	*cert = NULL;
	return 0;
    }

    *cert = hx509_cert_ref(mem->certs.val[*iter]);
    (*iter)++;
    return 0;
}
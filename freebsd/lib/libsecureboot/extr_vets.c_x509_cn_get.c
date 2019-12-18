#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_5__* vtable; } ;
typedef  TYPE_1__ br_x509_minimal_context ;
struct TYPE_14__ {int /*<<< orphan*/  data_len; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ br_x509_certificate ;
struct TYPE_15__ {unsigned char* oid; char* buf; size_t len; int /*<<< orphan*/  status; } ;
typedef  TYPE_3__ br_name_element ;
struct TYPE_16__ {int (* end_chain ) (TYPE_5__**) ;int /*<<< orphan*/  (* end_cert ) (TYPE_5__**) ;int /*<<< orphan*/  (* append ) (TYPE_5__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* start_cert ) (TYPE_5__**,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* start_chain ) (TYPE_5__**,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  br_sha256_vtable ; 
 int /*<<< orphan*/  br_x509_minimal_init (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_x509_minimal_set_name_elements (TYPE_1__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_5__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (TYPE_5__**) ; 
 int stub5 (TYPE_5__**) ; 

__attribute__((used)) static char *
x509_cn_get(br_x509_certificate *xc, char *buf, size_t len)
{
	br_x509_minimal_context mc;
	br_name_element cn;
	unsigned char cn_oid[4];
	int err;

	if (buf == NULL)
		return (buf);
	/*
	 * We want the commonName field
	 * the OID we want is 2,5,4,3 - but DER encoded
	 */
	cn_oid[0] = 3;
	cn_oid[1] = 0x55;
	cn_oid[2] = 4;
	cn_oid[3] = 3;
	cn.oid = cn_oid;
	cn.buf = buf;
	cn.len = len;
	cn.buf[0] = '\0';

	br_x509_minimal_init(&mc, &br_sha256_vtable, NULL, 0);
	br_x509_minimal_set_name_elements(&mc, &cn, 1);
	/* the below actually does the work - updates cn.status */
	mc.vtable->start_chain(&mc.vtable, NULL);
	mc.vtable->start_cert(&mc.vtable, xc->data_len);
	mc.vtable->append(&mc.vtable, xc->data, xc->data_len);
	mc.vtable->end_cert(&mc.vtable);
	/* we don' actually care about cert status - just its name */
	err = mc.vtable->end_chain(&mc.vtable);

	if (!cn.status)
		buf = NULL;
	return (buf);
}
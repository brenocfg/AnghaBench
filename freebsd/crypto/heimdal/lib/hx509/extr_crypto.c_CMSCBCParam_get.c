#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* hx509_crypto ;
typedef  int /*<<< orphan*/  hx509_context ;
struct TYPE_8__ {size_t length; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ heim_octet_string ;
struct TYPE_7__ {int /*<<< orphan*/ * param; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_MALLOC_ENCODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,TYPE_2__ const*,size_t*,int) ; 
 int /*<<< orphan*/  CMSCBCParameter ; 
 int /*<<< orphan*/  _hx509_abort (char*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_clear_error_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
CMSCBCParam_get(hx509_context context, const hx509_crypto crypto,
		 const heim_octet_string *ivec, heim_octet_string *param)
{
    size_t size;
    int ret;

    assert(crypto->param == NULL);
    if (ivec == NULL)
	return 0;

    ASN1_MALLOC_ENCODE(CMSCBCParameter, param->data, param->length,
		       ivec, &size, ret);
    if (ret == 0 && size != param->length)
	_hx509_abort("Internal asn1 encoder failure");
    if (ret)
	hx509_clear_error_string(context);
    return ret;
}
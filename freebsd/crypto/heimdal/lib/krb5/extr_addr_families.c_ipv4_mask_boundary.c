#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_8__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct TYPE_7__ {TYPE_3__ address; void* addr_type; } ;
typedef  TYPE_1__ krb5_address ;

/* Variables and functions */
 void* KRB5_ADDRESS_INET ; 
 int KRB5_PROG_ATYPE_NOSUPP ; 
 int /*<<< orphan*/  N_ (char*,char*) ; 
 int /*<<< orphan*/  _krb5_get_int (int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _krb5_put_int (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_data_alloc (TYPE_3__*,int) ; 
 int /*<<< orphan*/  krb5_free_address (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int
ipv4_mask_boundary(krb5_context context, const krb5_address *inaddr,
		   unsigned long len, krb5_address *low, krb5_address *high)
{
    unsigned long ia;
    uint32_t l, h, m = 0xffffffff;

    if (len > 32) {
	krb5_set_error_message(context, KRB5_PROG_ATYPE_NOSUPP,
			       N_("IPv4 prefix too large (%ld)", "len"), len);
	return KRB5_PROG_ATYPE_NOSUPP;
    }
    m = m << (32 - len);

    _krb5_get_int(inaddr->address.data, &ia, inaddr->address.length);

    l = ia & m;
    h = l | ~m;

    low->addr_type = KRB5_ADDRESS_INET;
    if(krb5_data_alloc(&low->address, 4) != 0)
	return -1;
    _krb5_put_int(low->address.data, l, low->address.length);

    high->addr_type = KRB5_ADDRESS_INET;
    if(krb5_data_alloc(&high->address, 4) != 0) {
	krb5_free_address(context, low);
	return -1;
    }
    _krb5_put_int(high->address.data, h, high->address.length);

    return 0;
}
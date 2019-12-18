#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_error_code ;
struct TYPE_3__ {int /*<<< orphan*/  address; int /*<<< orphan*/  addr_type; } ;
typedef  TYPE_1__ krb5_address ;

/* Variables and functions */
 int /*<<< orphan*/  KRB5_ADDRESS_INET ; 
 int /*<<< orphan*/  krb5_data_copy (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,char const*,int) ; 

__attribute__((used)) static krb5_error_code
ipv4_h_addr2addr (const char *addr,
		  krb5_address *a)
{
    unsigned char buf[4];

    a->addr_type = KRB5_ADDRESS_INET;
    memcpy(buf, addr, 4);
    return krb5_data_copy(&a->address, buf, 4);
}
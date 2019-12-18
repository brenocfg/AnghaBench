#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct in_addr {int /*<<< orphan*/  s_addr; } ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_5__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {TYPE_2__ address; int /*<<< orphan*/  addr_type; } ;
typedef  TYPE_1__ krb5_address ;

/* Variables and functions */
 int /*<<< orphan*/  KRB5_ADDRESS_INET ; 
 int /*<<< orphan*/  _krb5_put_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ inet_aton (char const*,struct in_addr*) ; 
 scalar_t__ krb5_data_alloc (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strncasecmp (char const*,char*,int) ; 

__attribute__((used)) static int
ipv4_parse_addr (krb5_context context, const char *address, krb5_address *addr)
{
    const char *p;
    struct in_addr a;

    p = strchr(address, ':');
    if(p) {
	p++;
	if(strncasecmp(address, "ip:", p - address) != 0 &&
	   strncasecmp(address, "ip4:", p - address) != 0 &&
	   strncasecmp(address, "ipv4:", p - address) != 0 &&
	   strncasecmp(address, "inet:", p - address) != 0)
	    return -1;
    } else
	p = address;
    if(inet_aton(p, &a) == 0)
	return -1;
    addr->addr_type = KRB5_ADDRESS_INET;
    if(krb5_data_alloc(&addr->address, 4) != 0)
	return -1;
    _krb5_put_int(addr->address.data, ntohl(a.s_addr), addr->address.length);
    return 0;
}
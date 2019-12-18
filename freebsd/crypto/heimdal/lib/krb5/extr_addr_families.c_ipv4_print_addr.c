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
struct in_addr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
struct TYPE_5__ {TYPE_1__ address; } ;
typedef  TYPE_2__ krb5_address ;

/* Variables and functions */
 char* inet_ntoa (struct in_addr) ; 
 int /*<<< orphan*/  memcpy (struct in_addr*,int /*<<< orphan*/ ,int) ; 
 int snprintf (char*,size_t,char*,char*) ; 

__attribute__((used)) static int
ipv4_print_addr (const krb5_address *addr, char *str, size_t len)
{
    struct in_addr ia;

    memcpy (&ia, addr->address.data, 4);

    return snprintf (str, len, "IPv4:%s", inet_ntoa(ia));
}
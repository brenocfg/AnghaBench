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
struct sockaddr {int sa_family; } ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_address ;

/* Variables and functions */
 int /*<<< orphan*/  krb5_free_address (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_print_address (int /*<<< orphan*/ *,char*,size_t,size_t*) ; 
 scalar_t__ krb5_sockaddr2address (int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int) ; 

__attribute__((used)) static void
addr_to_string(krb5_context context,
	       struct sockaddr *addr, size_t addr_len, char *str, size_t len)
{
    krb5_address a;
    if(krb5_sockaddr2address(context, addr, &a) == 0) {
	if(krb5_print_address(&a, str, len, &len) == 0) {
	    krb5_free_address(context, &a);
	    return;
	}
	krb5_free_address(context, &a);
    }
    snprintf(str, len, "<family=%d>", addr->sa_family);
}
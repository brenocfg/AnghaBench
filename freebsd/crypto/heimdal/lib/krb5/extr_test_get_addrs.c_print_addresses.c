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
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_3__ {int len; int /*<<< orphan*/ * val; } ;
typedef  TYPE_1__ krb5_addresses ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  krb5_print_address (int /*<<< orphan*/ *,char*,int,size_t*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void
print_addresses (krb5_context context, const krb5_addresses *addrs)
{
    int i;
    char buf[256];
    size_t len;

    for (i = 0; i < addrs->len; ++i) {
	krb5_print_address (&addrs->val[i], buf, sizeof(buf), &len);
	printf ("%s\n", buf);
    }
}
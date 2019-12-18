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
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int strlen (char const*) ; 
 int /*<<< orphan*/  truncated_addr (int /*<<< orphan*/ ,char const*,int,int) ; 

__attribute__((used)) static void
check_truncation(krb5_context context, const char *addr)
{
    int i, len = strlen(addr);

    truncated_addr(context, addr, len, len);

    for (i = 0; i < len; i++)
	truncated_addr(context, addr, i, len);
}
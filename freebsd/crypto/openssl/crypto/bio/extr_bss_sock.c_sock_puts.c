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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int sock_write (int /*<<< orphan*/ *,char const*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int sock_puts(BIO *bp, const char *str)
{
    int n, ret;

    n = strlen(str);
    ret = sock_write(bp, str, n);
    return ret;
}
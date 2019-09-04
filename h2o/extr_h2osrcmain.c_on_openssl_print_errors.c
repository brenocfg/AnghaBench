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

/* Variables and functions */
 int /*<<< orphan*/  fwrite (char const*,int,size_t,void*) ; 

__attribute__((used)) static int on_openssl_print_errors(const char *str, size_t len, void *fp)
{
    fwrite(str, 1, len, fp);
    return (int)len;
}
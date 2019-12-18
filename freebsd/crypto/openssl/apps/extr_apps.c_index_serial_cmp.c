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
typedef  char* OPENSSL_CSTRING ;

/* Variables and functions */
 size_t DB_serial ; 
 int strcmp (char const*,char const*) ; 

__attribute__((used)) static int index_serial_cmp(const OPENSSL_CSTRING *a,
                            const OPENSSL_CSTRING *b)
{
    const char *aa, *bb;

    for (aa = a[DB_serial]; *aa == '0'; aa++) ;
    for (bb = b[DB_serial]; *bb == '0'; bb++) ;
    return strcmp(aa, bb);
}
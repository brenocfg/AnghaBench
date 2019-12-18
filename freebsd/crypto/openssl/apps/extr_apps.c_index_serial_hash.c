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
 unsigned long OPENSSL_LH_strhash (char const*) ; 

__attribute__((used)) static unsigned long index_serial_hash(const OPENSSL_CSTRING *a)
{
    const char *n;

    n = a[DB_serial];
    while (*n == '0')
        n++;
    return OPENSSL_LH_strhash(n);
}
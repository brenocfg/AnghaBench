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
typedef  int /*<<< orphan*/  heim_general_string ;

/* Variables and functions */
 int ASN1_OVERFLOW ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/  const,size_t) ; 
 size_t strlen (int /*<<< orphan*/  const) ; 

int
der_put_general_string (unsigned char *p, size_t len,
			const heim_general_string *str, size_t *size)
{
    size_t slen = strlen(*str);

    if (len < slen)
	return ASN1_OVERFLOW;
    p -= slen;
    memcpy (p+1, *str, slen);
    *size = slen;
    return 0;
}
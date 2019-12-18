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
typedef  scalar_t__ Der_type ;
typedef  int /*<<< orphan*/  Der_class ;

/* Variables and functions */
 int ASN1_BAD_ID ; 
 int der_match_tag2 (unsigned char const*,size_t,int /*<<< orphan*/ ,scalar_t__*,unsigned int,size_t*) ; 

int
der_match_tag (const unsigned char *p, size_t len,
	       Der_class class, Der_type type,
	       unsigned int tag, size_t *size)
{
    Der_type thistype;
    int e;

    e = der_match_tag2(p, len, class, &thistype, tag, size);
    if (e) return e;
    if (thistype != type) return ASN1_BAD_ID;
    return 0;
}
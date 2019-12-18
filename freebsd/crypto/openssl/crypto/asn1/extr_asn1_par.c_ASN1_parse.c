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
 int asn1_parse2 (int /*<<< orphan*/ *,unsigned char const**,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int ASN1_parse(BIO *bp, const unsigned char *pp, long len, int indent)
{
    return asn1_parse2(bp, &pp, len, 0, 0, indent, 0);
}
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
 int /*<<< orphan*/  ASN1_BIT_STRING_set_bit (void*,long,int) ; 
 int /*<<< orphan*/  ASN1_F_BITSTR_CB ; 
 int /*<<< orphan*/  ASN1_R_INVALID_NUMBER ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 long strtoul (char const*,char**,int) ; 

__attribute__((used)) static int bitstr_cb(const char *elem, int len, void *bitstr)
{
    long bitnum;
    char *eptr;
    if (!elem)
        return 0;
    bitnum = strtoul(elem, &eptr, 10);
    if (eptr && *eptr && (eptr != elem + len))
        return 0;
    if (bitnum < 0) {
        ASN1err(ASN1_F_BITSTR_CB, ASN1_R_INVALID_NUMBER);
        return 0;
    }
    if (!ASN1_BIT_STRING_set_bit(bitstr, bitnum, 1)) {
        ASN1err(ASN1_F_BITSTR_CB, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    return 1;
}
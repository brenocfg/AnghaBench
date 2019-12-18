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
 int V_ASN1_NEG_ENUMERATED ; 
 int V_ASN1_NEG_INTEGER ; 

const char *ASN1_tag2str(int tag)
{
    static const char *const tag2str[] = {
        /* 0-4 */
        "EOC", "BOOLEAN", "INTEGER", "BIT STRING", "OCTET STRING",
        /* 5-9 */
        "NULL", "OBJECT", "OBJECT DESCRIPTOR", "EXTERNAL", "REAL",
        /* 10-13 */
        "ENUMERATED", "<ASN1 11>", "UTF8STRING", "<ASN1 13>",
        /* 15-17 */
        "<ASN1 14>", "<ASN1 15>", "SEQUENCE", "SET",
        /* 18-20 */
        "NUMERICSTRING", "PRINTABLESTRING", "T61STRING",
        /* 21-24 */
        "VIDEOTEXSTRING", "IA5STRING", "UTCTIME", "GENERALIZEDTIME",
        /* 25-27 */
        "GRAPHICSTRING", "VISIBLESTRING", "GENERALSTRING",
        /* 28-30 */
        "UNIVERSALSTRING", "<ASN1 29>", "BMPSTRING"
    };

    if ((tag == V_ASN1_NEG_INTEGER) || (tag == V_ASN1_NEG_ENUMERATED))
        tag &= ~0x100;

    if (tag < 0 || tag > 30)
        return "(unknown)";
    return tag2str[tag];
}
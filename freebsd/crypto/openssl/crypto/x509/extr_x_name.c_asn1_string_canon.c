#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int length; unsigned char* data; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ ASN1_STRING ;

/* Variables and functions */
 int ASN1_MASK_CANON ; 
 int /*<<< orphan*/  ASN1_STRING_copy (TYPE_1__*,TYPE_1__ const*) ; 
 int ASN1_STRING_to_UTF8 (unsigned char**,TYPE_1__ const*) ; 
 int ASN1_tag2bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_ASN1_UTF8STRING ; 
 int /*<<< orphan*/  ossl_isascii (unsigned char) ; 
 scalar_t__ ossl_isspace (unsigned char) ; 
 int /*<<< orphan*/  ossl_tolower (unsigned char) ; 

__attribute__((used)) static int asn1_string_canon(ASN1_STRING *out, const ASN1_STRING *in)
{
    unsigned char *to, *from;
    int len, i;

    /* If type not in bitmask just copy string across */
    if (!(ASN1_tag2bit(in->type) & ASN1_MASK_CANON)) {
        if (!ASN1_STRING_copy(out, in))
            return 0;
        return 1;
    }

    out->type = V_ASN1_UTF8STRING;
    out->length = ASN1_STRING_to_UTF8(&out->data, in);
    if (out->length == -1)
        return 0;

    to = out->data;
    from = to;

    len = out->length;

    /*
     * Convert string in place to canonical form. Ultimately we may need to
     * handle a wider range of characters but for now ignore anything with
     * MSB set and rely on the ossl_isspace() to fail on bad characters without
     * needing isascii or range checks as well.
     */

    /* Ignore leading spaces */
    while (len > 0 && ossl_isspace(*from)) {
        from++;
        len--;
    }

    to = from + len;

    /* Ignore trailing spaces */
    while (len > 0 && ossl_isspace(to[-1])) {
        to--;
        len--;
    }

    to = out->data;

    i = 0;
    while (i < len) {
        /* If not ASCII set just copy across */
        if (!ossl_isascii(*from)) {
            *to++ = *from++;
            i++;
        }
        /* Collapse multiple spaces */
        else if (ossl_isspace(*from)) {
            /* Copy one space across */
            *to++ = ' ';
            /*
             * Ignore subsequent spaces. Note: don't need to check len here
             * because we know the last character is a non-space so we can't
             * overflow.
             */
            do {
                from++;
                i++;
            }
            while (ossl_isspace(*from));
        } else {
            *to++ = ossl_tolower(*from);
            from++;
            i++;
        }
    }

    out->length = to - out->data;

    return 1;

}
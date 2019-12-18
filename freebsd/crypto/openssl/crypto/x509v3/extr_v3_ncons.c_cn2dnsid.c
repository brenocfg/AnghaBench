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
typedef  int /*<<< orphan*/  ASN1_STRING ;

/* Variables and functions */
 int ASN1_STRING_to_UTF8 (unsigned char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int X509_V_ERR_OUT_OF_MEM ; 
 int X509_V_ERR_UNSUPPORTED_NAME_SYNTAX ; 
 int X509_V_OK ; 
 size_t strlen (char*) ; 

__attribute__((used)) static int cn2dnsid(ASN1_STRING *cn, unsigned char **dnsid, size_t *idlen)
{
    int utf8_length;
    unsigned char *utf8_value;
    int i;
    int isdnsname = 0;

    /* Don't leave outputs uninitialized */
    *dnsid = NULL;
    *idlen = 0;

    /*-
     * Per RFC 6125, DNS-IDs representing internationalized domain names appear
     * in certificates in A-label encoded form:
     *
     *   https://tools.ietf.org/html/rfc6125#section-6.4.2
     *
     * The same applies to CNs which are intended to represent DNS names.
     * However, while in the SAN DNS-IDs are IA5Strings, as CNs they may be
     * needlessly encoded in 16-bit Unicode.  We perform a conversion to UTF-8
     * to ensure that we get an ASCII representation of any CNs that are
     * representable as ASCII, but just not encoded as ASCII.  The UTF-8 form
     * may contain some non-ASCII octets, and that's fine, such CNs are not
     * valid legacy DNS names.
     *
     * Note, 'int' is the return type of ASN1_STRING_to_UTF8() so that's what
     * we must use for 'utf8_length'.
     */
    if ((utf8_length = ASN1_STRING_to_UTF8(&utf8_value, cn)) < 0)
        return X509_V_ERR_OUT_OF_MEM;

    /*
     * Some certificates have had names that include a *trailing* NUL byte.
     * Remove these harmless NUL characters. They would otherwise yield false
     * alarms with the following embedded NUL check.
     */
    while (utf8_length > 0 && utf8_value[utf8_length - 1] == '\0')
        --utf8_length;

    /* Reject *embedded* NULs */
    if ((size_t)utf8_length != strlen((char *)utf8_value)) {
        OPENSSL_free(utf8_value);
        return X509_V_ERR_UNSUPPORTED_NAME_SYNTAX;
    }

    /*
     * XXX: Deviation from strict DNS name syntax, also check names with '_'
     * Check DNS name syntax, any '-' or '.' must be internal,
     * and on either side of each '.' we can't have a '-' or '.'.
     *
     * If the name has just one label, we don't consider it a DNS name.  This
     * means that "CN=sometld" cannot be precluded by DNS name constraints, but
     * that is not a problem.
     */
    for (i = 0; i < utf8_length; ++i) {
        unsigned char c = utf8_value[i];

        if ((c >= 'a' && c <= 'z')
            || (c >= 'A' && c <= 'Z')
            || (c >= '0' && c <= '9')
            || c == '_')
            continue;

        /* Dot and hyphen cannot be first or last. */
        if (i > 0 && i < utf8_length - 1) {
            if (c == '-')
                continue;
            /*
             * Next to a dot the preceding and following characters must not be
             * another dot or a hyphen.  Otherwise, record that the name is
             * plausible, since it has two or more labels.
             */
            if (c == '.'
                && utf8_value[i + 1] != '.'
                && utf8_value[i - 1] != '-'
                && utf8_value[i + 1] != '-') {
                isdnsname = 1;
                continue;
            }
        }
        isdnsname = 0;
        break;
    }

    if (isdnsname) {
        *dnsid = utf8_value;
        *idlen = (size_t)utf8_length;
        return X509_V_OK;
    }
    OPENSSL_free(utf8_value);
    return X509_V_OK;
}
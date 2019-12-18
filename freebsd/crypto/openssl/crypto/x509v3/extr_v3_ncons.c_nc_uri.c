#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int length; scalar_t__ data; } ;
typedef  TYPE_1__ ASN1_IA5STRING ;

/* Variables and functions */
 int X509_V_ERR_PERMITTED_VIOLATION ; 
 int X509_V_ERR_UNSUPPORTED_NAME_SYNTAX ; 
 int X509_V_OK ; 
 scalar_t__ ia5ncasecmp (char const*,char const*,int) ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int nc_uri(ASN1_IA5STRING *uri, ASN1_IA5STRING *base)
{
    const char *baseptr = (char *)base->data;
    const char *hostptr = (char *)uri->data;
    const char *p = strchr(hostptr, ':');
    int hostlen;
    /* Check for foo:// and skip past it */
    if (!p || (p[1] != '/') || (p[2] != '/'))
        return X509_V_ERR_UNSUPPORTED_NAME_SYNTAX;
    hostptr = p + 3;

    /* Determine length of hostname part of URI */

    /* Look for a port indicator as end of hostname first */

    p = strchr(hostptr, ':');
    /* Otherwise look for trailing slash */
    if (!p)
        p = strchr(hostptr, '/');

    if (!p)
        hostlen = strlen(hostptr);
    else
        hostlen = p - hostptr;

    if (hostlen == 0)
        return X509_V_ERR_UNSUPPORTED_NAME_SYNTAX;

    /* Special case: initial '.' is RHS match */
    if (*baseptr == '.') {
        if (hostlen > base->length) {
            p = hostptr + hostlen - base->length;
            if (ia5ncasecmp(p, baseptr, base->length) == 0)
                return X509_V_OK;
        }
        return X509_V_ERR_PERMITTED_VIOLATION;
    }

    if ((base->length != (int)hostlen)
        || ia5ncasecmp(hostptr, baseptr, hostlen))
        return X509_V_ERR_PERMITTED_VIOLATION;

    return X509_V_OK;

}
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
struct TYPE_4__ {scalar_t__ length; scalar_t__ data; } ;
typedef  TYPE_1__ ASN1_IA5STRING ;

/* Variables and functions */
 int X509_V_ERR_PERMITTED_VIOLATION ; 
 int X509_V_OK ; 
 scalar_t__ ia5casecmp (char*,char*) ; 

__attribute__((used)) static int nc_dns(ASN1_IA5STRING *dns, ASN1_IA5STRING *base)
{
    char *baseptr = (char *)base->data;
    char *dnsptr = (char *)dns->data;
    /* Empty matches everything */
    if (!*baseptr)
        return X509_V_OK;
    /*
     * Otherwise can add zero or more components on the left so compare RHS
     * and if dns is longer and expect '.' as preceding character.
     */
    if (dns->length > base->length) {
        dnsptr += dns->length - base->length;
        if (*baseptr != '.' && dnsptr[-1] != '.')
            return X509_V_ERR_PERMITTED_VIOLATION;
    }

    if (ia5casecmp(baseptr, dnsptr))
        return X509_V_ERR_PERMITTED_VIOLATION;

    return X509_V_OK;

}
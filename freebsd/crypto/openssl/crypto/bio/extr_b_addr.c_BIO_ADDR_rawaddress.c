#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  sun_path; } ;
struct TYPE_9__ {scalar_t__ sa_family; } ;
struct TYPE_8__ {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  sin_addr; } ;
struct TYPE_11__ {TYPE_4__ s_un; TYPE_3__ sa; TYPE_2__ s_in6; TYPE_1__ s_in; } ;
typedef  TYPE_5__ BIO_ADDR ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ AF_UNIX ; 
 int /*<<< orphan*/  memcpy (void*,void const*,size_t) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 

int BIO_ADDR_rawaddress(const BIO_ADDR *ap, void *p, size_t *l)
{
    size_t len = 0;
    const void *addrptr = NULL;

    if (ap->sa.sa_family == AF_INET) {
        len = sizeof(ap->s_in.sin_addr);
        addrptr = &ap->s_in.sin_addr;
    }
#ifdef AF_INET6
    else if (ap->sa.sa_family == AF_INET6) {
        len = sizeof(ap->s_in6.sin6_addr);
        addrptr = &ap->s_in6.sin6_addr;
    }
#endif
#ifdef AF_UNIX
    else if (ap->sa.sa_family == AF_UNIX) {
        len = strlen(ap->s_un.sun_path);
        addrptr = &ap->s_un.sun_path;
    }
#endif

    if (addrptr == NULL)
        return 0;

    if (p != NULL) {
        memcpy(p, addrptr, len);
    }
    if (l != NULL)
        *l = len;

    return 1;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_un {int dummy; } ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_un; int /*<<< orphan*/  s_in6; int /*<<< orphan*/  s_in; } ;
typedef  TYPE_1__ BIO_ADDR ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ AF_UNIX ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr const*,int) ; 

int BIO_ADDR_make(BIO_ADDR *ap, const struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        memcpy(&(ap->s_in), sa, sizeof(struct sockaddr_in));
        return 1;
    }
#ifdef AF_INET6
    if (sa->sa_family == AF_INET6) {
        memcpy(&(ap->s_in6), sa, sizeof(struct sockaddr_in6));
        return 1;
    }
#endif
#ifdef AF_UNIX
    if (sa->sa_family == AF_UNIX) {
        memcpy(&(ap->s_un), sa, sizeof(struct sockaddr_un));
        return 1;
    }
#endif

    return 0;
}
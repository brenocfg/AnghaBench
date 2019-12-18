#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ version; int /*<<< orphan*/ * (* cmeth ) () ;} ;
typedef  TYPE_2__ version_info ;
struct TYPE_12__ {scalar_t__ version; int /*<<< orphan*/  server; TYPE_1__* method; } ;
struct TYPE_10__ {int version; } ;
typedef  int /*<<< orphan*/  SSL_METHOD ;
typedef  TYPE_3__ SSL ;

/* Variables and functions */
#define  DTLS_ANY_VERSION 129 
 int TLS1_3_VERSION ; 
#define  TLS_ANY_VERSION 128 
 TYPE_2__* dtls_version_table ; 
 scalar_t__ is_tls13_capable (TYPE_3__ const*) ; 
 scalar_t__ ssl_method_error (TYPE_3__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 () ; 
 int /*<<< orphan*/ * stub2 () ; 
 TYPE_2__* tls_version_table ; 
 scalar_t__ version_cmp (TYPE_3__ const*,int,scalar_t__) ; 

int ssl_version_supported(const SSL *s, int version, const SSL_METHOD **meth)
{
    const version_info *vent;
    const version_info *table;

    switch (s->method->version) {
    default:
        /* Version should match method version for non-ANY method */
        return version_cmp(s, version, s->version) == 0;
    case TLS_ANY_VERSION:
        table = tls_version_table;
        break;
    case DTLS_ANY_VERSION:
        table = dtls_version_table;
        break;
    }

    for (vent = table;
         vent->version != 0 && version_cmp(s, version, vent->version) <= 0;
         ++vent) {
        if (vent->cmeth != NULL
                && version_cmp(s, version, vent->version) == 0
                && ssl_method_error(s, vent->cmeth()) == 0
                && (!s->server
                    || version != TLS1_3_VERSION
                    || is_tls13_capable(s))) {
            if (meth != NULL)
                *meth = vent->cmeth();
            return 1;
        }
    }
    return 0;
}
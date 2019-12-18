#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ resp_len; int /*<<< orphan*/ * resp; } ;
struct TYPE_6__ {TYPE_1__ ocsp; int /*<<< orphan*/  status_type; } ;
struct TYPE_7__ {TYPE_2__ ext; scalar_t__ server; } ;
typedef  TYPE_3__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TLSEXT_STATUSTYPE_nothing ; 

__attribute__((used)) static int init_status_request(SSL *s, unsigned int context)
{
    if (s->server) {
        s->ext.status_type = TLSEXT_STATUSTYPE_nothing;
    } else {
        /*
         * Ensure we get sensible values passed to tlsext_status_cb in the event
         * that we don't receive a status message
         */
        OPENSSL_free(s->ext.ocsp.resp);
        s->ext.ocsp.resp = NULL;
        s->ext.ocsp.resp_len = 0;
    }

    return 1;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* ctx; } ;
typedef  TYPE_2__ ptls_t ;
struct TYPE_10__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
typedef  TYPE_3__ ptls_iovec_t ;
struct TYPE_11__ {int /*<<< orphan*/  (* cb ) (TYPE_4__*,TYPE_2__*,char const*,char*,char*) ;} ;
struct TYPE_8__ {TYPE_4__* log_event; } ;

/* Variables and functions */
 int PTLS_MAX_DIGEST_SIZE ; 
 int /*<<< orphan*/  ptls_hexdump (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,TYPE_2__*,char const*,char*,char*) ; 

__attribute__((used)) static void log_secret(ptls_t *tls, const char *type, ptls_iovec_t secret)
{
    if (tls->ctx->log_event != NULL) {
        char hexbuf[PTLS_MAX_DIGEST_SIZE * 2 + 1];
        ptls_hexdump(hexbuf, secret.base, secret.len);
        tls->ctx->log_event->cb(tls->ctx->log_event, tls, type, "%s", hexbuf);
    }
}
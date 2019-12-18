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
struct TYPE_3__ {size_t ticket_appdata_len; int /*<<< orphan*/ * ticket_appdata; } ;
typedef  TYPE_1__ SSL_SESSION ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OPENSSL_memdup (void const*,size_t) ; 

int SSL_SESSION_set1_ticket_appdata(SSL_SESSION *ss, const void *data, size_t len)
{
    OPENSSL_free(ss->ticket_appdata);
    ss->ticket_appdata_len = 0;
    if (data == NULL || len == 0) {
        ss->ticket_appdata = NULL;
        return 1;
    }
    ss->ticket_appdata = OPENSSL_memdup(data, len);
    if (ss->ticket_appdata != NULL) {
        ss->ticket_appdata_len = len;
        return 1;
    }
    return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t alpn_selected_len; int /*<<< orphan*/ * alpn_selected; } ;
struct TYPE_5__ {TYPE_1__ ext; } ;
typedef  TYPE_2__ SSL_SESSION ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OPENSSL_memdup (unsigned char const*,size_t) ; 

int SSL_SESSION_set1_alpn_selected(SSL_SESSION *s, const unsigned char *alpn,
                                   size_t len)
{
    OPENSSL_free(s->ext.alpn_selected);
    if (alpn == NULL || len == 0) {
        s->ext.alpn_selected = NULL;
        s->ext.alpn_selected_len = 0;
        return 1;
    }
    s->ext.alpn_selected = OPENSSL_memdup(alpn, len);
    if (s->ext.alpn_selected == NULL) {
        s->ext.alpn_selected_len = 0;
        return 0;
    }
    s->ext.alpn_selected_len = len;

    return 1;
}
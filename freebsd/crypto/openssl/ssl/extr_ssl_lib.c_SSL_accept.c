#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * handshake_func; } ;
typedef  TYPE_1__ SSL ;

/* Variables and functions */
 int SSL_do_handshake (TYPE_1__*) ; 
 int /*<<< orphan*/  SSL_set_accept_state (TYPE_1__*) ; 

int SSL_accept(SSL *s)
{
    if (s->handshake_func == NULL) {
        /* Not properly initialized yet */
        SSL_set_accept_state(s);
    }

    return SSL_do_handshake(s);
}
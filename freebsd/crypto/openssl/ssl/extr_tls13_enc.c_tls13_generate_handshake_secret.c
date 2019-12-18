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
struct TYPE_5__ {int /*<<< orphan*/  handshake_secret; int /*<<< orphan*/  early_secret; } ;
typedef  TYPE_1__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  ssl_handshake_md (TYPE_1__*) ; 
 int tls13_generate_secret (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char const*,size_t,unsigned char*) ; 

int tls13_generate_handshake_secret(SSL *s, const unsigned char *insecret,
                                size_t insecretlen)
{
    /* Calls SSLfatal() if required */
    return tls13_generate_secret(s, ssl_handshake_md(s), s->early_secret,
                                 insecret, insecretlen,
                                 (unsigned char *)&s->handshake_secret);
}
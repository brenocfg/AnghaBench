#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  WPACKET ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_EXT_TLS1_3_ENCRYPTED_EXTENSIONS ; 
 int /*<<< orphan*/  tls_construct_extensions (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tls_construct_encrypted_extensions(SSL *s, WPACKET *pkt)
{
    if (!tls_construct_extensions(s, pkt, SSL_EXT_TLS1_3_ENCRYPTED_EXTENSIONS,
                                  NULL, 0)) {
        /* SSLfatal() already called */
        return 0;
    }

    return 1;
}
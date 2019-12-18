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
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  RAW_EXTENSION ;
typedef  int /*<<< orphan*/  PACKET ;
typedef  int /*<<< orphan*/  MSG_PROCESS_RETURN ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_PROCESS_CONTINUE_READING ; 
 int /*<<< orphan*/  MSG_PROCESS_ERROR ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_as_length_prefixed_2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_EXT_TLS1_3_ENCRYPTED_EXTENSIONS ; 
 int /*<<< orphan*/  SSL_F_TLS_PROCESS_ENCRYPTED_EXTENSIONS ; 
 int /*<<< orphan*/  SSL_R_LENGTH_MISMATCH ; 
 int /*<<< orphan*/  SSLfatal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_collect_extensions (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tls_parse_all_extensions (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static MSG_PROCESS_RETURN tls_process_encrypted_extensions(SSL *s, PACKET *pkt)
{
    PACKET extensions;
    RAW_EXTENSION *rawexts = NULL;

    if (!PACKET_as_length_prefixed_2(pkt, &extensions)
            || PACKET_remaining(pkt) != 0) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PROCESS_ENCRYPTED_EXTENSIONS,
                 SSL_R_LENGTH_MISMATCH);
        goto err;
    }

    if (!tls_collect_extensions(s, &extensions,
                                SSL_EXT_TLS1_3_ENCRYPTED_EXTENSIONS, &rawexts,
                                NULL, 1)
            || !tls_parse_all_extensions(s, SSL_EXT_TLS1_3_ENCRYPTED_EXTENSIONS,
                                         rawexts, NULL, 0, 1)) {
        /* SSLfatal() already called */
        goto err;
    }

    OPENSSL_free(rawexts);
    return MSG_PROCESS_CONTINUE_READING;

 err:
    OPENSSL_free(rawexts);
    return MSG_PROCESS_ERROR;
}
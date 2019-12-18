#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ version; TYPE_3__* d1; TYPE_2__* s3; } ;
struct TYPE_13__ {int /*<<< orphan*/  handshake_read_seq; } ;
struct TYPE_11__ {int /*<<< orphan*/ * new_cipher; } ;
struct TYPE_12__ {int change_cipher_spec; TYPE_1__ tmp; } ;
typedef  TYPE_4__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;
typedef  int /*<<< orphan*/  MSG_PROCESS_RETURN ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_CTRL_DGRAM_SCTP_AUTH_CCS_RCVD ; 
 int /*<<< orphan*/  BIO_ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ DTLS1_BAD_VER ; 
 int DTLS1_CCS_HEADER_LENGTH ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  MSG_PROCESS_CONTINUE_READING ; 
 int /*<<< orphan*/  MSG_PROCESS_ERROR ; 
 size_t PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL3_CC_READ ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_AD_UNEXPECTED_MESSAGE ; 
 int /*<<< orphan*/  SSL_F_TLS_PROCESS_CHANGE_CIPHER_SPEC ; 
 scalar_t__ SSL_IS_DTLS (TYPE_4__*) ; 
 int /*<<< orphan*/  SSL_R_BAD_CHANGE_CIPHER_SPEC ; 
 int /*<<< orphan*/  SSL_R_CCS_RECEIVED_EARLY ; 
 int /*<<< orphan*/  SSL_get_wbio (TYPE_4__*) ; 
 int /*<<< orphan*/  SSLfatal (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtls1_reset_seq_numbers (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl3_do_change_cipher_spec (TYPE_4__*) ; 

MSG_PROCESS_RETURN tls_process_change_cipher_spec(SSL *s, PACKET *pkt)
{
    size_t remain;

    remain = PACKET_remaining(pkt);
    /*
     * 'Change Cipher Spec' is just a single byte, which should already have
     * been consumed by ssl_get_message() so there should be no bytes left,
     * unless we're using DTLS1_BAD_VER, which has an extra 2 bytes
     */
    if (SSL_IS_DTLS(s)) {
        if ((s->version == DTLS1_BAD_VER
             && remain != DTLS1_CCS_HEADER_LENGTH + 1)
            || (s->version != DTLS1_BAD_VER
                && remain != DTLS1_CCS_HEADER_LENGTH - 1)) {
            SSLfatal(s, SSL_AD_DECODE_ERROR,
                     SSL_F_TLS_PROCESS_CHANGE_CIPHER_SPEC,
                    SSL_R_BAD_CHANGE_CIPHER_SPEC);
            return MSG_PROCESS_ERROR;
        }
    } else {
        if (remain != 0) {
            SSLfatal(s, SSL_AD_DECODE_ERROR,
                     SSL_F_TLS_PROCESS_CHANGE_CIPHER_SPEC,
                     SSL_R_BAD_CHANGE_CIPHER_SPEC);
            return MSG_PROCESS_ERROR;
        }
    }

    /* Check we have a cipher to change to */
    if (s->s3->tmp.new_cipher == NULL) {
        SSLfatal(s, SSL_AD_UNEXPECTED_MESSAGE,
                 SSL_F_TLS_PROCESS_CHANGE_CIPHER_SPEC, SSL_R_CCS_RECEIVED_EARLY);
        return MSG_PROCESS_ERROR;
    }

    s->s3->change_cipher_spec = 1;
    if (!ssl3_do_change_cipher_spec(s)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_CHANGE_CIPHER_SPEC,
                 ERR_R_INTERNAL_ERROR);
        return MSG_PROCESS_ERROR;
    }

    if (SSL_IS_DTLS(s)) {
        dtls1_reset_seq_numbers(s, SSL3_CC_READ);

        if (s->version == DTLS1_BAD_VER)
            s->d1->handshake_read_seq++;

#ifndef OPENSSL_NO_SCTP
        /*
         * Remember that a CCS has been received, so that an old key of
         * SCTP-Auth can be deleted when a CCS is sent. Will be ignored if no
         * SCTP is used
         */
        BIO_ctrl(SSL_get_wbio(s), BIO_CTRL_DGRAM_SCTP_AUTH_CCS_RCVD, 1, NULL);
#endif
    }

    return MSG_PROCESS_CONTINUE_READING;
}
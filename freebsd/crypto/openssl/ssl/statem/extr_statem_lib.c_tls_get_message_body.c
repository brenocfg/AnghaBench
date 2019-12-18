#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {size_t init_num; unsigned char* init_msg; int /*<<< orphan*/  msg_callback_arg; TYPE_4__* init_buf; int /*<<< orphan*/  version; int /*<<< orphan*/  (* msg_callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,size_t,TYPE_5__*,int /*<<< orphan*/ ) ;TYPE_3__* s3; int /*<<< orphan*/  rlayer; int /*<<< orphan*/  rwstate; TYPE_1__* method; } ;
struct TYPE_16__ {scalar_t__* data; } ;
struct TYPE_14__ {scalar_t__ message_type; size_t message_size; } ;
struct TYPE_15__ {TYPE_2__ tmp; } ;
struct TYPE_13__ {int (* ssl_read_bytes ) (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*,size_t,int /*<<< orphan*/ ,size_t*) ;} ;
typedef  TYPE_5__ SSL ;

/* Variables and functions */
 scalar_t__ RECORD_LAYER_is_sslv2_record (int /*<<< orphan*/ *) ; 
 int SERVER_HELLO_RANDOM_OFFSET ; 
 int /*<<< orphan*/  SSL2_VERSION ; 
 size_t SSL3_HM_HEADER_LENGTH ; 
 scalar_t__ SSL3_MT_CHANGE_CIPHER_SPEC ; 
 scalar_t__ SSL3_MT_FINISHED ; 
 scalar_t__ SSL3_MT_KEY_UPDATE ; 
 scalar_t__ SSL3_MT_NEWSESSION_TICKET ; 
 scalar_t__ SSL3_MT_SERVER_HELLO ; 
 int SSL3_RANDOM_SIZE ; 
 int /*<<< orphan*/  SSL3_RT_HANDSHAKE ; 
 int /*<<< orphan*/  SSL_IS_TLS13 (TYPE_5__*) ; 
 int /*<<< orphan*/  SSL_READING ; 
 int /*<<< orphan*/  hrrrandom ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  ssl3_finish_mac (TYPE_5__*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  ssl3_take_mac (TYPE_5__*) ; 
 int stub1 (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*,size_t,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,size_t,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,size_t,TYPE_5__*,int /*<<< orphan*/ ) ; 

int tls_get_message_body(SSL *s, size_t *len)
{
    size_t n, readbytes;
    unsigned char *p;
    int i;

    if (s->s3->tmp.message_type == SSL3_MT_CHANGE_CIPHER_SPEC) {
        /* We've already read everything in */
        *len = (unsigned long)s->init_num;
        return 1;
    }

    p = s->init_msg;
    n = s->s3->tmp.message_size - s->init_num;
    while (n > 0) {
        i = s->method->ssl_read_bytes(s, SSL3_RT_HANDSHAKE, NULL,
                                      &p[s->init_num], n, 0, &readbytes);
        if (i <= 0) {
            s->rwstate = SSL_READING;
            *len = 0;
            return 0;
        }
        s->init_num += readbytes;
        n -= readbytes;
    }

    /*
     * If receiving Finished, record MAC of prior handshake messages for
     * Finished verification.
     */
    if (*(s->init_buf->data) == SSL3_MT_FINISHED && !ssl3_take_mac(s)) {
        /* SSLfatal() already called */
        *len = 0;
        return 0;
    }

    /* Feed this message into MAC computation. */
    if (RECORD_LAYER_is_sslv2_record(&s->rlayer)) {
        if (!ssl3_finish_mac(s, (unsigned char *)s->init_buf->data,
                             s->init_num)) {
            /* SSLfatal() already called */
            *len = 0;
            return 0;
        }
        if (s->msg_callback)
            s->msg_callback(0, SSL2_VERSION, 0, s->init_buf->data,
                            (size_t)s->init_num, s, s->msg_callback_arg);
    } else {
        /*
         * We defer feeding in the HRR until later. We'll do it as part of
         * processing the message
         * The TLsv1.3 handshake transcript stops at the ClientFinished
         * message.
         */
#define SERVER_HELLO_RANDOM_OFFSET  (SSL3_HM_HEADER_LENGTH + 2)
        /* KeyUpdate and NewSessionTicket do not need to be added */
        if (!SSL_IS_TLS13(s) || (s->s3->tmp.message_type != SSL3_MT_NEWSESSION_TICKET
                                 && s->s3->tmp.message_type != SSL3_MT_KEY_UPDATE)) {
            if (s->s3->tmp.message_type != SSL3_MT_SERVER_HELLO
                    || s->init_num < SERVER_HELLO_RANDOM_OFFSET + SSL3_RANDOM_SIZE
                    || memcmp(hrrrandom,
                              s->init_buf->data + SERVER_HELLO_RANDOM_OFFSET,
                              SSL3_RANDOM_SIZE) != 0) {
                if (!ssl3_finish_mac(s, (unsigned char *)s->init_buf->data,
                                     s->init_num + SSL3_HM_HEADER_LENGTH)) {
                    /* SSLfatal() already called */
                    *len = 0;
                    return 0;
                }
            }
        }
        if (s->msg_callback)
            s->msg_callback(0, s->version, SSL3_RT_HANDSHAKE, s->init_buf->data,
                            (size_t)s->init_num + SSL3_HM_HEADER_LENGTH, s,
                            s->msg_callback_arg);
    }

    *len = s->init_num;
    return 1;
}
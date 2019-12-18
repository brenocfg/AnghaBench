#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct hm_header_st {size_t msg_len; size_t frag_off; size_t frag_len; int /*<<< orphan*/  seq; int /*<<< orphan*/  type; } ;
struct TYPE_13__ {TYPE_4__* d1; TYPE_2__* s3; int /*<<< orphan*/  init_buf; } ;
struct TYPE_11__ {scalar_t__ frag_off; size_t msg_len; int /*<<< orphan*/  seq; int /*<<< orphan*/  type; } ;
struct TYPE_12__ {TYPE_3__ r_msg_hdr; } ;
struct TYPE_9__ {size_t message_size; int /*<<< orphan*/  message_type; } ;
struct TYPE_10__ {TYPE_1__ tmp; } ;
typedef  TYPE_5__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_MEM_grow_clean (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ DTLS1_HM_HEADER_LENGTH ; 
 int /*<<< orphan*/  ERR_R_BUF_LIB ; 
 int /*<<< orphan*/  SSL_AD_ILLEGAL_PARAMETER ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_DTLS1_PREPROCESS_FRAGMENT ; 
 int /*<<< orphan*/  SSL_R_EXCESSIVE_MESSAGE_SIZE ; 
 int /*<<< orphan*/  SSLfatal (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t dtls1_max_handshake_message_len (TYPE_5__*) ; 

__attribute__((used)) static int dtls1_preprocess_fragment(SSL *s, struct hm_header_st *msg_hdr)
{
    size_t frag_off, frag_len, msg_len;

    msg_len = msg_hdr->msg_len;
    frag_off = msg_hdr->frag_off;
    frag_len = msg_hdr->frag_len;

    /* sanity checking */
    if ((frag_off + frag_len) > msg_len
            || msg_len > dtls1_max_handshake_message_len(s)) {
        SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER, SSL_F_DTLS1_PREPROCESS_FRAGMENT,
                 SSL_R_EXCESSIVE_MESSAGE_SIZE);
        return 0;
    }

    if (s->d1->r_msg_hdr.frag_off == 0) { /* first fragment */
        /*
         * msg_len is limited to 2^24, but is effectively checked against
         * dtls_max_handshake_message_len(s) above
         */
        if (!BUF_MEM_grow_clean(s->init_buf, msg_len + DTLS1_HM_HEADER_LENGTH)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_DTLS1_PREPROCESS_FRAGMENT,
                     ERR_R_BUF_LIB);
            return 0;
        }

        s->s3->tmp.message_size = msg_len;
        s->d1->r_msg_hdr.msg_len = msg_len;
        s->s3->tmp.message_type = msg_hdr->type;
        s->d1->r_msg_hdr.type = msg_hdr->type;
        s->d1->r_msg_hdr.seq = msg_hdr->seq;
    } else if (msg_len != s->d1->r_msg_hdr.msg_len) {
        /*
         * They must be playing with us! BTW, failure to enforce upper limit
         * would open possibility for buffer overrun.
         */
        SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER, SSL_F_DTLS1_PREPROCESS_FRAGMENT,
                 SSL_R_EXCESSIVE_MESSAGE_SIZE);
        return 0;
    }

    return 1;
}
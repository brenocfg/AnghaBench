#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct dtls1_retransmit_state {int /*<<< orphan*/  epoch; int /*<<< orphan*/  session; int /*<<< orphan*/  compress; int /*<<< orphan*/  write_hash; int /*<<< orphan*/  enc_write_ctx; } ;
typedef  int /*<<< orphan*/  seq64be ;
struct TYPE_17__ {scalar_t__ data; } ;
typedef  TYPE_5__ pitem ;
struct TYPE_14__ {int /*<<< orphan*/  epoch; int /*<<< orphan*/  session; int /*<<< orphan*/  compress; int /*<<< orphan*/  write_hash; int /*<<< orphan*/  enc_write_ctx; } ;
struct TYPE_15__ {scalar_t__ is_ccs; TYPE_2__ saved_retransmit_state; int /*<<< orphan*/  frag_len; int /*<<< orphan*/  seq; scalar_t__ msg_len; int /*<<< orphan*/  type; } ;
struct TYPE_18__ {TYPE_3__ msg_header; int /*<<< orphan*/  fragment; } ;
typedef  TYPE_6__ hm_fragment ;
struct TYPE_19__ {int /*<<< orphan*/  wbio; TYPE_4__* d1; int /*<<< orphan*/  rlayer; int /*<<< orphan*/  session; int /*<<< orphan*/  compress; int /*<<< orphan*/  write_hash; int /*<<< orphan*/  enc_write_ctx; scalar_t__ init_num; TYPE_1__* init_buf; } ;
struct TYPE_16__ {int retransmitting; int /*<<< orphan*/  sent_messages; } ;
struct TYPE_13__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_7__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_flush (int /*<<< orphan*/ ) ; 
 unsigned long DTLS1_CCS_HEADER_LENGTH ; 
 unsigned long DTLS1_HM_HEADER_LENGTH ; 
 int /*<<< orphan*/  DTLS_RECORD_LAYER_get_w_epoch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DTLS_RECORD_LAYER_set_saved_w_epoch (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL3_RT_CHANGE_CIPHER_SPEC ; 
 int /*<<< orphan*/  SSL3_RT_HANDSHAKE ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_DTLS1_RETRANSMIT_MESSAGE ; 
 int /*<<< orphan*/  SSLfatal (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dtls1_do_write (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtls1_set_message_header_int (TYPE_7__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 TYPE_5__* pqueue_find (int /*<<< orphan*/ ,unsigned char*) ; 

int dtls1_retransmit_message(SSL *s, unsigned short seq, int *found)
{
    int ret;
    /* XDTLS: for now assuming that read/writes are blocking */
    pitem *item;
    hm_fragment *frag;
    unsigned long header_length;
    unsigned char seq64be[8];
    struct dtls1_retransmit_state saved_state;

    /* XDTLS:  the requested message ought to be found, otherwise error */
    memset(seq64be, 0, sizeof(seq64be));
    seq64be[6] = (unsigned char)(seq >> 8);
    seq64be[7] = (unsigned char)seq;

    item = pqueue_find(s->d1->sent_messages, seq64be);
    if (item == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_DTLS1_RETRANSMIT_MESSAGE,
                 ERR_R_INTERNAL_ERROR);
        *found = 0;
        return 0;
    }

    *found = 1;
    frag = (hm_fragment *)item->data;

    if (frag->msg_header.is_ccs)
        header_length = DTLS1_CCS_HEADER_LENGTH;
    else
        header_length = DTLS1_HM_HEADER_LENGTH;

    memcpy(s->init_buf->data, frag->fragment,
           frag->msg_header.msg_len + header_length);
    s->init_num = frag->msg_header.msg_len + header_length;

    dtls1_set_message_header_int(s, frag->msg_header.type,
                                 frag->msg_header.msg_len,
                                 frag->msg_header.seq, 0,
                                 frag->msg_header.frag_len);

    /* save current state */
    saved_state.enc_write_ctx = s->enc_write_ctx;
    saved_state.write_hash = s->write_hash;
    saved_state.compress = s->compress;
    saved_state.session = s->session;
    saved_state.epoch = DTLS_RECORD_LAYER_get_w_epoch(&s->rlayer);

    s->d1->retransmitting = 1;

    /* restore state in which the message was originally sent */
    s->enc_write_ctx = frag->msg_header.saved_retransmit_state.enc_write_ctx;
    s->write_hash = frag->msg_header.saved_retransmit_state.write_hash;
    s->compress = frag->msg_header.saved_retransmit_state.compress;
    s->session = frag->msg_header.saved_retransmit_state.session;
    DTLS_RECORD_LAYER_set_saved_w_epoch(&s->rlayer,
                                        frag->msg_header.
                                        saved_retransmit_state.epoch);

    ret = dtls1_do_write(s, frag->msg_header.is_ccs ?
                         SSL3_RT_CHANGE_CIPHER_SPEC : SSL3_RT_HANDSHAKE);

    /* restore current state */
    s->enc_write_ctx = saved_state.enc_write_ctx;
    s->write_hash = saved_state.write_hash;
    s->compress = saved_state.compress;
    s->session = saved_state.session;
    DTLS_RECORD_LAYER_set_saved_w_epoch(&s->rlayer, saved_state.epoch);

    s->d1->retransmitting = 0;

    (void)BIO_flush(s->wbio);
    return ret;
}
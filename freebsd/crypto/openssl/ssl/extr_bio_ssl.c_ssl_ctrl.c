#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {long renegotiate_timeout; unsigned long last_time; long renegotiate_count; long num_renegotiates; TYPE_2__* ssl; int /*<<< orphan*/  byte_count; } ;
struct TYPE_18__ {void* rbio; void* wbio; TYPE_1__* method; int /*<<< orphan*/  handshake_func; } ;
struct TYPE_17__ {int /*<<< orphan*/  ssl_accept; int /*<<< orphan*/  ssl_connect; } ;
typedef  TYPE_2__ SSL ;
typedef  TYPE_3__ BIO_SSL ;
typedef  void BIO ;

/* Variables and functions */
#define  BIO_CTRL_DUP 150 
#define  BIO_CTRL_FLUSH 149 
#define  BIO_CTRL_GET_CLOSE 148 
#define  BIO_CTRL_INFO 147 
#define  BIO_CTRL_PENDING 146 
#define  BIO_CTRL_POP 145 
#define  BIO_CTRL_PUSH 144 
#define  BIO_CTRL_RESET 143 
#define  BIO_CTRL_SET_CALLBACK 142 
#define  BIO_CTRL_SET_CLOSE 141 
#define  BIO_CTRL_WPENDING 140 
#define  BIO_C_DO_STATE_MACHINE 139 
#define  BIO_C_GET_FD 138 
#define  BIO_C_GET_SSL 137 
#define  BIO_C_GET_SSL_NUM_RENEGOTIATES 136 
#define  BIO_C_SET_SSL 135 
#define  BIO_C_SET_SSL_RENEGOTIATE_BYTES 134 
#define  BIO_C_SET_SSL_RENEGOTIATE_TIMEOUT 133 
#define  BIO_C_SSL_MODE 132 
 int BIO_FLAGS_IO_SPECIAL ; 
 int BIO_FLAGS_READ ; 
 int BIO_FLAGS_SHOULD_RETRY ; 
 int BIO_FLAGS_WRITE ; 
 int /*<<< orphan*/  BIO_RR_SSL_X509_LOOKUP ; 
 int /*<<< orphan*/  BIO_clear_retry_flags (void*) ; 
 int /*<<< orphan*/  BIO_copy_next_retry (void*) ; 
 long BIO_ctrl (void*,int,long,void*) ; 
 TYPE_3__* BIO_get_data (void*) ; 
 int /*<<< orphan*/  BIO_get_retry_reason (void*) ; 
 long BIO_get_shutdown (void*) ; 
 void* BIO_next (void*) ; 
 long BIO_pending (void*) ; 
 int /*<<< orphan*/  BIO_push (void*,void*) ; 
 int /*<<< orphan*/  BIO_set_flags (void*,int) ; 
 int /*<<< orphan*/  BIO_set_init (void*,int) ; 
 int /*<<< orphan*/  BIO_set_next (void*,void*) ; 
 int /*<<< orphan*/  BIO_set_retry_reason (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_set_retry_special (void*) ; 
 int /*<<< orphan*/  BIO_set_shutdown (void*,int) ; 
 int /*<<< orphan*/  BIO_up_ref (void*) ; 
#define  SSL_ERROR_WANT_CONNECT 131 
#define  SSL_ERROR_WANT_READ 130 
#define  SSL_ERROR_WANT_WRITE 129 
#define  SSL_ERROR_WANT_X509_LOOKUP 128 
 int /*<<< orphan*/  SSL_clear (TYPE_2__*) ; 
 scalar_t__ SSL_do_handshake (TYPE_2__*) ; 
 TYPE_2__* SSL_dup (TYPE_2__*) ; 
 int /*<<< orphan*/  SSL_free (TYPE_2__*) ; 
 int /*<<< orphan*/  SSL_get_error (TYPE_2__*,int) ; 
 void* SSL_get_rbio (TYPE_2__*) ; 
 long SSL_pending (TYPE_2__*) ; 
 int /*<<< orphan*/  SSL_set_accept_state (TYPE_2__*) ; 
 int /*<<< orphan*/  SSL_set_bio (TYPE_2__*,void*,void*) ; 
 int /*<<< orphan*/  SSL_set_connect_state (TYPE_2__*) ; 
 int /*<<< orphan*/  SSL_shutdown (TYPE_2__*) ; 
 int /*<<< orphan*/  ssl_free (void*) ; 
 int /*<<< orphan*/  ssl_new (void*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long ssl_ctrl(BIO *b, int cmd, long num, void *ptr)
{
    SSL **sslp, *ssl;
    BIO_SSL *bs, *dbs;
    BIO *dbio, *bio;
    long ret = 1;
    BIO *next;

    bs = BIO_get_data(b);
    next = BIO_next(b);
    ssl = bs->ssl;
    if ((ssl == NULL) && (cmd != BIO_C_SET_SSL))
        return 0;
    switch (cmd) {
    case BIO_CTRL_RESET:
        SSL_shutdown(ssl);

        if (ssl->handshake_func == ssl->method->ssl_connect)
            SSL_set_connect_state(ssl);
        else if (ssl->handshake_func == ssl->method->ssl_accept)
            SSL_set_accept_state(ssl);

        if (!SSL_clear(ssl)) {
            ret = 0;
            break;
        }

        if (next != NULL)
            ret = BIO_ctrl(next, cmd, num, ptr);
        else if (ssl->rbio != NULL)
            ret = BIO_ctrl(ssl->rbio, cmd, num, ptr);
        else
            ret = 1;
        break;
    case BIO_CTRL_INFO:
        ret = 0;
        break;
    case BIO_C_SSL_MODE:
        if (num)                /* client mode */
            SSL_set_connect_state(ssl);
        else
            SSL_set_accept_state(ssl);
        break;
    case BIO_C_SET_SSL_RENEGOTIATE_TIMEOUT:
        ret = bs->renegotiate_timeout;
        if (num < 60)
            num = 5;
        bs->renegotiate_timeout = (unsigned long)num;
        bs->last_time = (unsigned long)time(NULL);
        break;
    case BIO_C_SET_SSL_RENEGOTIATE_BYTES:
        ret = bs->renegotiate_count;
        if ((long)num >= 512)
            bs->renegotiate_count = (unsigned long)num;
        break;
    case BIO_C_GET_SSL_NUM_RENEGOTIATES:
        ret = bs->num_renegotiates;
        break;
    case BIO_C_SET_SSL:
        if (ssl != NULL) {
            ssl_free(b);
            if (!ssl_new(b))
                return 0;
        }
        BIO_set_shutdown(b, num);
        ssl = (SSL *)ptr;
        bs->ssl = ssl;
        bio = SSL_get_rbio(ssl);
        if (bio != NULL) {
            if (next != NULL)
                BIO_push(bio, next);
            BIO_set_next(b, bio);
            BIO_up_ref(bio);
        }
        BIO_set_init(b, 1);
        break;
    case BIO_C_GET_SSL:
        if (ptr != NULL) {
            sslp = (SSL **)ptr;
            *sslp = ssl;
        } else
            ret = 0;
        break;
    case BIO_CTRL_GET_CLOSE:
        ret = BIO_get_shutdown(b);
        break;
    case BIO_CTRL_SET_CLOSE:
        BIO_set_shutdown(b, (int)num);
        break;
    case BIO_CTRL_WPENDING:
        ret = BIO_ctrl(ssl->wbio, cmd, num, ptr);
        break;
    case BIO_CTRL_PENDING:
        ret = SSL_pending(ssl);
        if (ret == 0)
            ret = BIO_pending(ssl->rbio);
        break;
    case BIO_CTRL_FLUSH:
        BIO_clear_retry_flags(b);
        ret = BIO_ctrl(ssl->wbio, cmd, num, ptr);
        BIO_copy_next_retry(b);
        break;
    case BIO_CTRL_PUSH:
        if ((next != NULL) && (next != ssl->rbio)) {
            /*
             * We are going to pass ownership of next to the SSL object...but
             * we don't own a reference to pass yet - so up ref
             */
            BIO_up_ref(next);
            SSL_set_bio(ssl, next, next);
        }
        break;
    case BIO_CTRL_POP:
        /* Only detach if we are the BIO explicitly being popped */
        if (b == ptr) {
            /* This will clear the reference we obtained during push */
            SSL_set_bio(ssl, NULL, NULL);
        }
        break;
    case BIO_C_DO_STATE_MACHINE:
        BIO_clear_retry_flags(b);

        BIO_set_retry_reason(b, 0);
        ret = (int)SSL_do_handshake(ssl);

        switch (SSL_get_error(ssl, (int)ret)) {
        case SSL_ERROR_WANT_READ:
            BIO_set_flags(b, BIO_FLAGS_READ | BIO_FLAGS_SHOULD_RETRY);
            break;
        case SSL_ERROR_WANT_WRITE:
            BIO_set_flags(b, BIO_FLAGS_WRITE | BIO_FLAGS_SHOULD_RETRY);
            break;
        case SSL_ERROR_WANT_CONNECT:
            BIO_set_flags(b, BIO_FLAGS_IO_SPECIAL | BIO_FLAGS_SHOULD_RETRY);
            BIO_set_retry_reason(b, BIO_get_retry_reason(next));
            break;
        case SSL_ERROR_WANT_X509_LOOKUP:
            BIO_set_retry_special(b);
            BIO_set_retry_reason(b, BIO_RR_SSL_X509_LOOKUP);
            break;
        default:
            break;
        }
        break;
    case BIO_CTRL_DUP:
        dbio = (BIO *)ptr;
        dbs = BIO_get_data(dbio);
        SSL_free(dbs->ssl);
        dbs->ssl = SSL_dup(ssl);
        dbs->num_renegotiates = bs->num_renegotiates;
        dbs->renegotiate_count = bs->renegotiate_count;
        dbs->byte_count = bs->byte_count;
        dbs->renegotiate_timeout = bs->renegotiate_timeout;
        dbs->last_time = bs->last_time;
        ret = (dbs->ssl != NULL);
        break;
    case BIO_C_GET_FD:
        ret = BIO_ctrl(ssl->rbio, cmd, num, ptr);
        break;
    case BIO_CTRL_SET_CALLBACK:
        ret = 0; /* use callback ctrl */
        break;
    default:
        ret = BIO_ctrl(ssl->rbio, cmd, num, ptr);
        break;
    }
    return ret;
}
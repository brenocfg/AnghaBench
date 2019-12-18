#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_5__* method; TYPE_3__* s3; TYPE_1__* session; scalar_t__ server; } ;
struct TYPE_14__ {TYPE_4__* ssl3_enc; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* change_cipher_state ) (TYPE_6__*,int) ;int /*<<< orphan*/  (* setup_key_block ) (TYPE_6__*) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  new_cipher; int /*<<< orphan*/ * key_block; } ;
struct TYPE_12__ {TYPE_2__ tmp; } ;
struct TYPE_10__ {scalar_t__ master_key_length; int /*<<< orphan*/  cipher; } ;
typedef  TYPE_6__ SSL ;

/* Variables and functions */
 int SSL3_CHANGE_CIPHER_CLIENT_READ ; 
 int SSL3_CHANGE_CIPHER_SERVER_READ ; 
 int /*<<< orphan*/  SSL_F_SSL3_DO_CHANGE_CIPHER_SPEC ; 
 int /*<<< orphan*/  SSL_R_CCS_RECEIVED_EARLY ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_6__*,int) ; 

int ssl3_do_change_cipher_spec(SSL *s)
{
    int i;

    if (s->server)
        i = SSL3_CHANGE_CIPHER_SERVER_READ;
    else
        i = SSL3_CHANGE_CIPHER_CLIENT_READ;

    if (s->s3->tmp.key_block == NULL) {
        if (s->session == NULL || s->session->master_key_length == 0) {
            /* might happen if dtls1_read_bytes() calls this */
            SSLerr(SSL_F_SSL3_DO_CHANGE_CIPHER_SPEC, SSL_R_CCS_RECEIVED_EARLY);
            return 0;
        }

        s->session->cipher = s->s3->tmp.new_cipher;
        if (!s->method->ssl3_enc->setup_key_block(s))
            return 0;
    }

    if (!s->method->ssl3_enc->change_cipher_state(s, i))
        return 0;

    return 1;
}
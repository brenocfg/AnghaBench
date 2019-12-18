#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* s3; int /*<<< orphan*/  rlayer; } ;
struct TYPE_6__ {int /*<<< orphan*/  total_renegotiations; int /*<<< orphan*/  num_renegotiations; scalar_t__ renegotiate; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  RECORD_LAYER_read_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RECORD_LAYER_write_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_in_init (TYPE_2__*) ; 
 int /*<<< orphan*/  ossl_statem_set_renegotiate (TYPE_2__*) ; 

int ssl3_renegotiate_check(SSL *s, int initok)
{
    int ret = 0;

    if (s->s3->renegotiate) {
        if (!RECORD_LAYER_read_pending(&s->rlayer)
            && !RECORD_LAYER_write_pending(&s->rlayer)
            && (initok || !SSL_in_init(s))) {
            /*
             * if we are the server, and we have sent a 'RENEGOTIATE'
             * message, we need to set the state machine into the renegotiate
             * state.
             */
            ossl_statem_set_renegotiate(s);
            s->s3->renegotiate = 0;
            s->s3->num_renegotiations++;
            s->s3->total_renegotiations++;
            ret = 1;
        }
    }
    return ret;
}
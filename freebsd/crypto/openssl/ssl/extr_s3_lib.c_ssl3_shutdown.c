#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int shutdown; TYPE_2__* s3; TYPE_1__* method; scalar_t__ quiet_shutdown; } ;
struct TYPE_10__ {scalar_t__ alert_dispatch; } ;
struct TYPE_9__ {int (* ssl_dispatch_alert ) (TYPE_3__*) ;int /*<<< orphan*/  (* ssl_read_bytes ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ;} ;
typedef  TYPE_3__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL3_AL_WARNING ; 
 int /*<<< orphan*/  SSL_AD_CLOSE_NOTIFY ; 
 int SSL_RECEIVED_SHUTDOWN ; 
 int SSL_SENT_SHUTDOWN ; 
 scalar_t__ SSL_in_before (TYPE_3__*) ; 
 int /*<<< orphan*/  ssl3_send_alert (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 

int ssl3_shutdown(SSL *s)
{
    int ret;

    /*
     * Don't do anything much if we have not done the handshake or we don't
     * want to send messages :-)
     */
    if (s->quiet_shutdown || SSL_in_before(s)) {
        s->shutdown = (SSL_SENT_SHUTDOWN | SSL_RECEIVED_SHUTDOWN);
        return 1;
    }

    if (!(s->shutdown & SSL_SENT_SHUTDOWN)) {
        s->shutdown |= SSL_SENT_SHUTDOWN;
        ssl3_send_alert(s, SSL3_AL_WARNING, SSL_AD_CLOSE_NOTIFY);
        /*
         * our shutdown alert has been sent now, and if it still needs to be
         * written, s->s3->alert_dispatch will be true
         */
        if (s->s3->alert_dispatch)
            return -1;        /* return WANT_WRITE */
    } else if (s->s3->alert_dispatch) {
        /* resend it if not sent */
        ret = s->method->ssl_dispatch_alert(s);
        if (ret == -1) {
            /*
             * we only get to return -1 here the 2nd/Nth invocation, we must
             * have already signalled return 0 upon a previous invocation,
             * return WANT_WRITE
             */
            return ret;
        }
    } else if (!(s->shutdown & SSL_RECEIVED_SHUTDOWN)) {
        size_t readbytes;
        /*
         * If we are waiting for a close from our peer, we are closed
         */
        s->method->ssl_read_bytes(s, 0, NULL, NULL, 0, 0, &readbytes);
        if (!(s->shutdown & SSL_RECEIVED_SHUTDOWN)) {
            return -1;        /* return WANT_READ */
        }
    }

    if ((s->shutdown == (SSL_SENT_SHUTDOWN | SSL_RECEIVED_SHUTDOWN)) &&
        !s->s3->alert_dispatch)
        return 1;
    else
        return 0;
}
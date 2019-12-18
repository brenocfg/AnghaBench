#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_4__* s3; TYPE_2__* method; int /*<<< orphan*/  server; } ;
struct TYPE_10__ {int /*<<< orphan*/  peer_finish_md_len; int /*<<< orphan*/  peer_finish_md; } ;
struct TYPE_11__ {TYPE_3__ tmp; } ;
struct TYPE_9__ {TYPE_1__* ssl3_enc; } ;
struct TYPE_8__ {char* server_finished_label; size_t server_finished_label_len; char* client_finished_label; size_t client_finished_label_len; int /*<<< orphan*/  (* final_finish_mac ) (TYPE_5__*,char const*,size_t,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_5__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_5__*,char const*,size_t,int /*<<< orphan*/ ) ; 

int ssl3_take_mac(SSL *s)
{
    const char *sender;
    size_t slen;

    if (!s->server) {
        sender = s->method->ssl3_enc->server_finished_label;
        slen = s->method->ssl3_enc->server_finished_label_len;
    } else {
        sender = s->method->ssl3_enc->client_finished_label;
        slen = s->method->ssl3_enc->client_finished_label_len;
    }

    s->s3->tmp.peer_finish_md_len =
        s->method->ssl3_enc->final_finish_mac(s, sender, slen,
                                              s->s3->tmp.peer_finish_md);

    if (s->s3->tmp.peer_finish_md_len == 0) {
        /* SSLfatal() already called */
        return 0;
    }

    return 1;
}
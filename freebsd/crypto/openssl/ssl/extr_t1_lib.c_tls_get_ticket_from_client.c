#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  session_id_len; int /*<<< orphan*/  session_id; TYPE_3__* pre_proc_exts; } ;
struct TYPE_11__ {int /*<<< orphan*/  data; int /*<<< orphan*/  present; } ;
struct TYPE_9__ {scalar_t__ ticket_expected; } ;
struct TYPE_10__ {scalar_t__ version; TYPE_1__ ext; } ;
typedef  int /*<<< orphan*/  SSL_TICKET_STATUS ;
typedef  int /*<<< orphan*/  SSL_SESSION ;
typedef  TYPE_2__ SSL ;
typedef  TYPE_3__ RAW_EXTENSION ;
typedef  TYPE_4__ CLIENTHELLO_MSG ;

/* Variables and functions */
 int /*<<< orphan*/  PACKET_data (int /*<<< orphan*/ *) ; 
 size_t PACKET_remaining (int /*<<< orphan*/ *) ; 
 scalar_t__ SSL3_VERSION ; 
 int /*<<< orphan*/  SSL_TICKET_NONE ; 
 size_t TLSEXT_IDX_session_ticket ; 
 int /*<<< orphan*/  tls_decrypt_ticket (TYPE_2__*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  tls_use_ticket (TYPE_2__*) ; 

SSL_TICKET_STATUS tls_get_ticket_from_client(SSL *s, CLIENTHELLO_MSG *hello,
                                             SSL_SESSION **ret)
{
    size_t size;
    RAW_EXTENSION *ticketext;

    *ret = NULL;
    s->ext.ticket_expected = 0;

    /*
     * If tickets disabled or not supported by the protocol version
     * (e.g. TLSv1.3) behave as if no ticket present to permit stateful
     * resumption.
     */
    if (s->version <= SSL3_VERSION || !tls_use_ticket(s))
        return SSL_TICKET_NONE;

    ticketext = &hello->pre_proc_exts[TLSEXT_IDX_session_ticket];
    if (!ticketext->present)
        return SSL_TICKET_NONE;

    size = PACKET_remaining(&ticketext->data);

    return tls_decrypt_ticket(s, PACKET_data(&ticketext->data), size,
                              hello->session_id, hello->session_id_len, ret);
}
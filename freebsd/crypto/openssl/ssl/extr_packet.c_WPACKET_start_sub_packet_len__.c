#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t lenbytes; unsigned char* packet_len; scalar_t__ pwritten; struct TYPE_7__* parent; } ;
typedef  TYPE_1__ WPACKET_SUB ;
struct TYPE_8__ {scalar_t__ written; TYPE_1__* subs; } ;
typedef  TYPE_2__ WPACKET ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int GETBUF (TYPE_2__*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  SSL_F_WPACKET_START_SUB_PACKET_LEN__ ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_allocate_bytes (TYPE_2__*,size_t,unsigned char**) ; 
 int /*<<< orphan*/  ossl_assert (int /*<<< orphan*/ ) ; 

int WPACKET_start_sub_packet_len__(WPACKET *pkt, size_t lenbytes)
{
    WPACKET_SUB *sub;
    unsigned char *lenchars;

    /* Internal API, so should not fail */
    if (!ossl_assert(pkt->subs != NULL))
        return 0;

    if ((sub = OPENSSL_zalloc(sizeof(*sub))) == NULL) {
        SSLerr(SSL_F_WPACKET_START_SUB_PACKET_LEN__, ERR_R_MALLOC_FAILURE);
        return 0;
    }

    sub->parent = pkt->subs;
    pkt->subs = sub;
    sub->pwritten = pkt->written + lenbytes;
    sub->lenbytes = lenbytes;

    if (lenbytes == 0) {
        sub->packet_len = 0;
        return 1;
    }

    if (!WPACKET_allocate_bytes(pkt, lenbytes, &lenchars))
        return 0;
    /* Convert to an offset in case the underlying BUF_MEM gets realloc'd */
    sub->packet_len = lenchars - GETBUF(pkt);

    return 1;
}
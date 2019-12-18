#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  duration; scalar_t__ size; } ;
struct TYPE_9__ {TYPE_3__ pkt; struct TYPE_9__* next; scalar_t__ serial; } ;
struct TYPE_8__ {int recycle_count; int alloc_count; int /*<<< orphan*/  cond; int /*<<< orphan*/  duration; int /*<<< orphan*/  size; int /*<<< orphan*/  nb_packets; TYPE_2__* last_pkt; TYPE_2__* first_pkt; scalar_t__ serial; TYPE_2__* recycle_pkt; scalar_t__ abort_request; } ;
typedef  TYPE_1__ PacketQueue ;
typedef  TYPE_2__ MyAVPacketList ;
typedef  TYPE_3__ AVPacket ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 scalar_t__ FFMAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIN_PKT_DURATION ; 
 int /*<<< orphan*/  SDL_CondSignal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int) ; 
 TYPE_2__* av_malloc (int) ; 
 int /*<<< orphan*/  ffp ; 
 TYPE_3__ flush_pkt ; 

__attribute__((used)) static int packet_queue_put_private(PacketQueue *q, AVPacket *pkt)
{
    MyAVPacketList *pkt1;

    if (q->abort_request)
       return -1;

#ifdef FFP_MERGE
    pkt1 = av_malloc(sizeof(MyAVPacketList));
#else
    pkt1 = q->recycle_pkt;
    if (pkt1) {
        q->recycle_pkt = pkt1->next;
        q->recycle_count++;
    } else {
        q->alloc_count++;
        pkt1 = av_malloc(sizeof(MyAVPacketList));
    }
#ifdef FFP_SHOW_PKT_RECYCLE
    int total_count = q->recycle_count + q->alloc_count;
    if (!(total_count % 50)) {
        av_log(ffp, AV_LOG_DEBUG, "pkt-recycle \t%d + \t%d = \t%d\n", q->recycle_count, q->alloc_count, total_count);
    }
#endif
#endif
    if (!pkt1)
        return -1;
    pkt1->pkt = *pkt;
    pkt1->next = NULL;
    if (pkt == &flush_pkt)
        q->serial++;
    pkt1->serial = q->serial;

    if (!q->last_pkt)
        q->first_pkt = pkt1;
    else
        q->last_pkt->next = pkt1;
    q->last_pkt = pkt1;
    q->nb_packets++;
    q->size += pkt1->pkt.size + sizeof(*pkt1);

    q->duration += FFMAX(pkt1->pkt.duration, MIN_PKT_DURATION);

    /* XXX: should duplicate packet data in DV case */
    SDL_CondSignal(q->cond);
    return 0;
}
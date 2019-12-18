#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  quicly_sentmap_t ;
typedef  int /*<<< orphan*/  quicly_sentmap_iter_t ;
struct TYPE_3__ {int packet_number; int sent_at; scalar_t__ ack_epoch; int bytes_in_flight; } ;
typedef  TYPE_1__ quicly_sent_packet_t ;

/* Variables and functions */
 int /*<<< orphan*/  QUICLY_SENTMAP_EVENT_EXPIRED ; 
 scalar_t__ UINT64_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int num_blocks (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int) ; 
 int /*<<< orphan*/  on_acked ; 
 scalar_t__ on_acked_ackcnt ; 
 int on_acked_callcnt ; 
 int /*<<< orphan*/  quicly_sentmap_allocate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quicly_sentmap_commit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  quicly_sentmap_dispose (int /*<<< orphan*/ *) ; 
 TYPE_1__* quicly_sentmap_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quicly_sentmap_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quicly_sentmap_init_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quicly_sentmap_prepare (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quicly_sentmap_skip (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quicly_sentmap_update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void test_sentmap(void)
{
    quicly_sentmap_t map;
    uint64_t at;
    size_t i;
    quicly_sentmap_iter_t iter;
    const quicly_sent_packet_t *sent;

    quicly_sentmap_init(&map);

    /* save 50 packets, with 2 frames each */
    for (at = 0; at < 10; ++at) {
        for (i = 1; i <= 5; ++i) {
            quicly_sentmap_prepare(&map, at * 5 + i, at, 0);
            quicly_sentmap_allocate(&map, on_acked);
            quicly_sentmap_allocate(&map, on_acked);
            quicly_sentmap_commit(&map, 1);
        }
    }

    /* check all acks */
    quicly_sentmap_init_iter(&map, &iter);
    for (at = 0; at < 10; ++at) {
        for (i = 1; i <= 5; ++i) {
            const quicly_sent_packet_t *sent = quicly_sentmap_get(&iter);
            ok(sent->packet_number == at * 5 + i);
            ok(sent->sent_at == at);
            ok(sent->ack_epoch == 0);
            ok(sent->bytes_in_flight == 1);
            quicly_sentmap_skip(&iter);
        }
    }
    ok(quicly_sentmap_get(&iter)->packet_number == UINT64_MAX);
    ok(num_blocks(&map) == 150 / 16 + 1);

    /* pop acks between 11 <= packet_number <= 40 */
    quicly_sentmap_init_iter(&map, &iter);
    while (quicly_sentmap_get(&iter)->packet_number <= 10)
        quicly_sentmap_skip(&iter);
    assert(quicly_sentmap_get(&iter)->packet_number == 11);
    while (quicly_sentmap_get(&iter)->packet_number <= 40)
        quicly_sentmap_update(&map, &iter, QUICLY_SENTMAP_EVENT_EXPIRED, NULL);
    ok(on_acked_callcnt == 30 * 4);
    ok(on_acked_ackcnt == 0);

    size_t cnt = 0;
    for (quicly_sentmap_init_iter(&map, &iter); (sent = quicly_sentmap_get(&iter))->packet_number != UINT64_MAX;
         quicly_sentmap_skip(&iter)) {
        ok(sent->bytes_in_flight != 0);
        ok(sent->packet_number <= 10 || 40 < sent->packet_number);
        ++cnt;
    }
    ok(cnt == 20);
    ok(num_blocks(&map) == 30 / 16 + 1 + 1 + 30 / 16 + 1);

    quicly_sentmap_dispose(&map);
}
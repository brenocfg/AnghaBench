#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
struct st_ptls_record_t {int member_1; int length; char const* fragment; int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {int /*<<< orphan*/ * base; } ;
struct TYPE_8__ {TYPE_1__ mess; } ;
struct TYPE_10__ {TYPE_2__ recvbuf; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_4__ ptls_t ;
struct TYPE_11__ {int count; TYPE_3__* vec; } ;
struct TYPE_9__ {int len; int is_end_of_record; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTLS_CONTENT_TYPE_HANDSHAKE ; 
 int PTLS_ERROR_IN_PROGRESS ; 
 int handle_handshake_record (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct st_ptls_record_t*,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ok (int) ; 
 TYPE_5__ test_fragmented_message_queue ; 
 int /*<<< orphan*/  test_fragmented_message_record ; 

__attribute__((used)) static void test_fragmented_message(void)
{
    ptls_t tls = {NULL};
    struct st_ptls_record_t rec = {PTLS_CONTENT_TYPE_HANDSHAKE, 0x0301};
    int ret;

#define SET_RECORD(lit)                                                                                                            \
    do {                                                                                                                           \
        rec.length = sizeof(lit) - 1;                                                                                              \
        rec.fragment = (const uint8_t *)(lit);                                                                                     \
    } while (0)

    /* not fragmented */
    test_fragmented_message_queue.count = 0;
    SET_RECORD("\x01\x00\x00\x03"
               "abc");
    ret = handle_handshake_record(&tls, test_fragmented_message_record, NULL, &rec, NULL);
    ok(ret == 0);
    ok(test_fragmented_message_queue.count == 1);
    ok(test_fragmented_message_queue.vec[0].len == rec.length);
    ok(memcmp(test_fragmented_message_queue.vec[0].buf, rec.fragment, rec.length) == 0);
    ok(test_fragmented_message_queue.vec[0].is_end_of_record);
    ok(tls.recvbuf.mess.base == NULL);

    /* fragmented */
    test_fragmented_message_queue.count = 0;
    SET_RECORD("\x01\x00\x00\x03"
               "a");
    ret = handle_handshake_record(&tls, test_fragmented_message_record, NULL, &rec, NULL);
    ok(ret == PTLS_ERROR_IN_PROGRESS);
    ok(tls.recvbuf.mess.base != NULL);
    ok(test_fragmented_message_queue.count == 0);
    SET_RECORD("bc\x02\x00\x00\x02"
               "de"
               "\x03");
    ret = handle_handshake_record(&tls, test_fragmented_message_record, NULL, &rec, NULL);
    ok(ret == PTLS_ERROR_IN_PROGRESS);
    ok(test_fragmented_message_queue.count == 2);
    ok(test_fragmented_message_queue.vec[0].len == 7);
    ok(memcmp(test_fragmented_message_queue.vec[0].buf,
              "\x01\x00\x00\x03"
              "abc",
              7) == 0);
    ok(!test_fragmented_message_queue.vec[0].is_end_of_record);
    ok(test_fragmented_message_queue.vec[1].len == 6);
    ok(memcmp(test_fragmented_message_queue.vec[1].buf,
              "\x02\x00\x00\x02"
              "de",
              6) == 0);
    ok(!test_fragmented_message_queue.vec[1].is_end_of_record);
    SET_RECORD("\x00\x00\x03"
               "end");
    ret = handle_handshake_record(&tls, test_fragmented_message_record, NULL, &rec, NULL);
    ok(ret == 0);
    ok(tls.recvbuf.mess.base == NULL);
    ok(test_fragmented_message_queue.count == 3);
    ok(test_fragmented_message_queue.vec[2].len == 7);
    ok(memcmp(test_fragmented_message_queue.vec[2].buf,
              "\x03\x00\x00\x03"
              "end",
              7) == 0);
    ok(test_fragmented_message_queue.vec[2].is_end_of_record);

#undef SET_RECORD
}
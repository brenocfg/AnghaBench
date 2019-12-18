#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct st_ptls_message_emitter_t {int dummy; } ;
typedef  int /*<<< orphan*/  ptls_t ;
struct TYPE_6__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
typedef  TYPE_2__ ptls_iovec_t ;
typedef  int /*<<< orphan*/  ptls_handshake_properties_t ;
struct TYPE_7__ {size_t count; TYPE_1__* vec; } ;
struct TYPE_5__ {int is_end_of_record; int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ test_fragmented_message_queue ; 

__attribute__((used)) static int test_fragmented_message_record(ptls_t *tls, struct st_ptls_message_emitter_t *emitter, ptls_iovec_t message,
                                          int is_end_of_record, ptls_handshake_properties_t *properties)
{
    memcpy(test_fragmented_message_queue.vec[test_fragmented_message_queue.count].buf, message.base, message.len);
    test_fragmented_message_queue.vec[test_fragmented_message_queue.count].len = message.len;
    test_fragmented_message_queue.vec[test_fragmented_message_queue.count].is_end_of_record = is_end_of_record;
    ++test_fragmented_message_queue.count;

    return 0;
}
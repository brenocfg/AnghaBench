#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {TYPE_2__* hashes; } ;
typedef  TYPE_3__ ptls_key_schedule_t ;
typedef  int /*<<< orphan*/  prefix ;
struct TYPE_7__ {TYPE_1__* algo; } ;
struct TYPE_6__ {int /*<<< orphan*/  digest_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTLS_HANDSHAKE_TYPE_MESSAGE_HASH ; 
 int /*<<< orphan*/  ptls__key_schedule_update_hash (TYPE_3__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void key_schedule_update_ch1hash_prefix(ptls_key_schedule_t *sched)
{
    uint8_t prefix[4] = {PTLS_HANDSHAKE_TYPE_MESSAGE_HASH, 0, 0, (uint8_t)sched->hashes[0].algo->digest_size};
    ptls__key_schedule_update_hash(sched, prefix, sizeof(prefix));
}
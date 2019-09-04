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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_10__ {TYPE_2__* hashes; } ;
typedef  TYPE_3__ ptls_key_schedule_t ;
struct TYPE_9__ {TYPE_1__* algo; } ;
struct TYPE_8__ {int /*<<< orphan*/  digest_size; } ;

/* Variables and functions */
 int PTLS_MAX_DIGEST_SIZE ; 
 int /*<<< orphan*/  key_schedule_extract_ch1hash (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_schedule_update_ch1hash_prefix (TYPE_3__*) ; 
 int /*<<< orphan*/  ptls__key_schedule_update_hash (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void key_schedule_transform_post_ch1hash(ptls_key_schedule_t *sched)
{
    uint8_t ch1hash[PTLS_MAX_DIGEST_SIZE];

    key_schedule_extract_ch1hash(sched, ch1hash);

    key_schedule_update_ch1hash_prefix(sched);
    ptls__key_schedule_update_hash(sched, ch1hash, sched->hashes[0].algo->digest_size);
}
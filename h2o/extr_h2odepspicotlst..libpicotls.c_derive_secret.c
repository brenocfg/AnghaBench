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
struct TYPE_7__ {TYPE_1__* hashes; } ;
typedef  TYPE_2__ ptls_key_schedule_t ;
typedef  int /*<<< orphan*/  hash_value ;
struct TYPE_8__ {int /*<<< orphan*/  (* final ) (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {TYPE_3__* ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTLS_HASH_FINAL_MODE_SNAPSHOT ; 
 int PTLS_MAX_DIGEST_SIZE ; 
 int derive_secret_with_hash (TYPE_2__*,void*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptls_clear_memory (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int derive_secret(ptls_key_schedule_t *sched, void *secret, const char *label)
{
    uint8_t hash_value[PTLS_MAX_DIGEST_SIZE];

    sched->hashes[0].ctx->final(sched->hashes[0].ctx, hash_value, PTLS_HASH_FINAL_MODE_SNAPSHOT);
    int ret = derive_secret_with_hash(sched, secret, label, hash_value);
    ptls_clear_memory(hash_value, sizeof(hash_value));
    return ret;
}
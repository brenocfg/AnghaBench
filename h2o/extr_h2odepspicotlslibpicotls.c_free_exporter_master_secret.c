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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {int /*<<< orphan*/ * one_rtt; int /*<<< orphan*/ * early; } ;
struct TYPE_11__ {TYPE_4__* key_schedule; TYPE_1__ exporter_master_secret; } ;
typedef  TYPE_5__ ptls_t ;
struct TYPE_10__ {TYPE_3__* hashes; } ;
struct TYPE_9__ {TYPE_2__* algo; } ;
struct TYPE_8__ {int /*<<< orphan*/  digest_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptls_clear_memory (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_exporter_master_secret(ptls_t *tls, int is_early)
{
    uint8_t *slot = is_early ? tls->exporter_master_secret.early : tls->exporter_master_secret.one_rtt;
    if (slot == NULL)
        return;
    assert(tls->key_schedule != NULL);
    ptls_clear_memory(slot, tls->key_schedule->hashes[0].algo->digest_size);
    free(slot);
}
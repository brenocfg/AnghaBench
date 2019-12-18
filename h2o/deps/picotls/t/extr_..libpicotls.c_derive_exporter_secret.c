#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {int /*<<< orphan*/ * one_rtt; int /*<<< orphan*/ * early; } ;
struct TYPE_13__ {TYPE_7__* key_schedule; TYPE_1__ exporter_master_secret; TYPE_4__* ctx; } ;
typedef  TYPE_5__ ptls_t ;
struct TYPE_14__ {TYPE_3__* hashes; } ;
struct TYPE_12__ {int /*<<< orphan*/  use_exporter; } ;
struct TYPE_11__ {TYPE_2__* algo; } ;
struct TYPE_10__ {int /*<<< orphan*/  digest_size; } ;

/* Variables and functions */
 int PTLS_ERROR_NO_MEMORY ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int derive_secret (TYPE_7__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  log_secret (TYPE_5__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptls_iovec_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int derive_exporter_secret(ptls_t *tls, int is_early)
{
    int ret;

    if (!tls->ctx->use_exporter)
        return 0;

    uint8_t **slot = is_early ? &tls->exporter_master_secret.early : &tls->exporter_master_secret.one_rtt;
    assert(*slot == NULL);
    if ((*slot = malloc(tls->key_schedule->hashes[0].algo->digest_size)) == NULL)
        return PTLS_ERROR_NO_MEMORY;

    if ((ret = derive_secret(tls->key_schedule, *slot, is_early ? "e exp master" : "exp master")) != 0)
        return ret;

    log_secret(tls, is_early ? "EARLY_EXPORTER_SECRET" : "EXPORTER_SECRET",
               ptls_iovec_init(*slot, tls->key_schedule->hashes[0].algo->digest_size));

    return 0;
}
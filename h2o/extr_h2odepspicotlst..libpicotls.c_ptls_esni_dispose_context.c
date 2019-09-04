#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__** cipher_suites; TYPE_2__** key_exchanges; } ;
typedef  TYPE_1__ ptls_esni_context_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* on_exchange ) (TYPE_2__**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__**) ; 
 int /*<<< orphan*/  ptls_iovec_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ptls_esni_dispose_context(ptls_esni_context_t *esni)
{
    size_t i;

    if (esni->key_exchanges != NULL) {
        for (i = 0; esni->key_exchanges[i] != NULL; ++i)
            esni->key_exchanges[i]->on_exchange(esni->key_exchanges + i, 1, NULL, ptls_iovec_init(NULL, 0));
        free(esni->key_exchanges);
    }
    free(esni->cipher_suites);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct st_ptls_esni_secret_t* base; } ;
struct TYPE_5__ {TYPE_1__ pubkey; } ;
struct TYPE_6__ {int len; struct st_ptls_esni_secret_t* base; } ;
struct st_ptls_esni_secret_t {TYPE_2__ client; TYPE_3__ secret; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct st_ptls_esni_secret_t*) ; 
 int /*<<< orphan*/  ptls_clear_memory (struct st_ptls_esni_secret_t*,int) ; 

__attribute__((used)) static void free_esni_secret(struct st_ptls_esni_secret_t **esni, int is_server)
{
    assert(*esni != NULL);
    if ((*esni)->secret.base != NULL) {
        ptls_clear_memory((*esni)->secret.base, (*esni)->secret.len);
        free((*esni)->secret.base);
    }
    if (!is_server)
        free((*esni)->client.pubkey.base);
    ptls_clear_memory((*esni), sizeof(**esni));
    free(*esni);
    *esni = NULL;
}
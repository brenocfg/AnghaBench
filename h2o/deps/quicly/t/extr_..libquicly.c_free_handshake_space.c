#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * aead; } ;
struct TYPE_3__ {TYPE_2__ egress; TYPE_2__ ingress; } ;
struct st_quicly_handshake_space_t {int /*<<< orphan*/  super; TYPE_1__ cipher; } ;

/* Variables and functions */
 int /*<<< orphan*/  dispose_cipher (TYPE_2__*) ; 
 int /*<<< orphan*/  do_free_pn_space (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_handshake_space(struct st_quicly_handshake_space_t **space)
{
    if (*space != NULL) {
        if ((*space)->cipher.ingress.aead != NULL)
            dispose_cipher(&(*space)->cipher.ingress);
        if ((*space)->cipher.egress.aead != NULL)
            dispose_cipher(&(*space)->cipher.egress);
        do_free_pn_space(&(*space)->super);
        *space = NULL;
    }
}
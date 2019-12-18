#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* s3; } ;
struct TYPE_5__ {scalar_t__ key_block_length; int /*<<< orphan*/ * key_block; } ;
struct TYPE_6__ {TYPE_1__ tmp; } ;
typedef  TYPE_3__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_clear_free (int /*<<< orphan*/ *,scalar_t__) ; 

void ssl3_cleanup_key_block(SSL *s)
{
    OPENSSL_clear_free(s->s3->tmp.key_block, s->s3->tmp.key_block_length);
    s->s3->tmp.key_block = NULL;
    s->s3->tmp.key_block_length = 0;
}
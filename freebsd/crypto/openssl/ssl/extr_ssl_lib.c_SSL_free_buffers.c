#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  rlayer; } ;
typedef  TYPE_1__ SSL ;
typedef  int /*<<< orphan*/  RECORD_LAYER ;

/* Variables and functions */
 scalar_t__ RECORD_LAYER_read_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RECORD_LAYER_release (int /*<<< orphan*/ *) ; 
 scalar_t__ RECORD_LAYER_write_pending (int /*<<< orphan*/ *) ; 

int SSL_free_buffers(SSL *ssl)
{
    RECORD_LAYER *rl = &ssl->rlayer;

    if (RECORD_LAYER_read_pending(rl) || RECORD_LAYER_write_pending(rl))
        return 0;

    RECORD_LAYER_release(rl);
    return 1;
}
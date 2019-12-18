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
struct TYPE_6__ {int /*<<< orphan*/  rrec; TYPE_1__* s; } ;
struct TYPE_5__ {int /*<<< orphan*/  rlayer; } ;
typedef  TYPE_1__ SSL ;
typedef  TYPE_2__ RECORD_LAYER ;

/* Variables and functions */
 int /*<<< orphan*/  RECORD_LAYER_set_first_record (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL3_RECORD_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_MAX_PIPELINES ; 

void RECORD_LAYER_init(RECORD_LAYER *rl, SSL *s)
{
    rl->s = s;
    RECORD_LAYER_set_first_record(&s->rlayer);
    SSL3_RECORD_clear(rl->rrec, SSL_MAX_PIPELINES);
}
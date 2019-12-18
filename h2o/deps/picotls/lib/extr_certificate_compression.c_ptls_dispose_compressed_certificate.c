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
struct TYPE_9__ {int /*<<< orphan*/  base; } ;
struct TYPE_10__ {TYPE_3__ bytes; } ;
struct TYPE_7__ {int /*<<< orphan*/  base; } ;
struct TYPE_8__ {TYPE_1__ bytes; } ;
struct TYPE_11__ {TYPE_4__ without_ocsp_status; TYPE_2__ with_ocsp_status; } ;
typedef  TYPE_5__ ptls_emit_compressed_certificate_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

void ptls_dispose_compressed_certificate(ptls_emit_compressed_certificate_t *self)
{
    free(self->with_ocsp_status.bytes.base);
    free(self->without_ocsp_status.bytes.base);
}
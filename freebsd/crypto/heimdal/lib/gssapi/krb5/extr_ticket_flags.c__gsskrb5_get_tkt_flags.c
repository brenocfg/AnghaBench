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
typedef  TYPE_3__* gsskrb5_ctx ;
struct TYPE_7__ {int /*<<< orphan*/  ctx_id_mutex; TYPE_1__* ticket; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {TYPE_2__ ticket; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ GSS_S_BAD_MECH ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_NO_CONTEXT ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ TicketFlags2int (int /*<<< orphan*/ ) ; 

OM_uint32
_gsskrb5_get_tkt_flags(OM_uint32 *minor_status,
		       gsskrb5_ctx ctx,
		       OM_uint32 *tkt_flags)
{
    if (ctx == NULL) {
	*minor_status = EINVAL;
	return GSS_S_NO_CONTEXT;
    }
    HEIMDAL_MUTEX_lock(&ctx->ctx_id_mutex);

    if (ctx->ticket == NULL) {
	HEIMDAL_MUTEX_unlock(&ctx->ctx_id_mutex);
	*minor_status = EINVAL;
	return GSS_S_BAD_MECH;
    }

    *tkt_flags = TicketFlags2int(ctx->ticket->ticket.flags);
    HEIMDAL_MUTEX_unlock(&ctx->ctx_id_mutex);

    *minor_status = 0;
    return GSS_S_COMPLETE;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* gsskrb5_ctx ;
typedef  int /*<<< orphan*/  gss_buffer_set_t ;
struct TYPE_10__ {int length; unsigned char* value; } ;
typedef  TYPE_4__ gss_buffer_desc ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_9__ {int /*<<< orphan*/  ctx_id_mutex; TYPE_2__* ticket; } ;
struct TYPE_7__ {int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {TYPE_1__ ticket; } ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  GSS_S_BAD_MECH ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TicketFlags2int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _gsskrb5_encode_om_uint32 (int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  _gsskrb5_set_status (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gss_add_buffer_set_member (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static OM_uint32 inquire_sec_context_tkt_flags
           (OM_uint32 *minor_status,
            const gsskrb5_ctx context_handle,
            gss_buffer_set_t *data_set)
{
    OM_uint32 tkt_flags;
    unsigned char buf[4];
    gss_buffer_desc value;

    HEIMDAL_MUTEX_lock(&context_handle->ctx_id_mutex);

    if (context_handle->ticket == NULL) {
	HEIMDAL_MUTEX_unlock(&context_handle->ctx_id_mutex);
	_gsskrb5_set_status(EINVAL, "No ticket from which to obtain flags");
	*minor_status = EINVAL;
	return GSS_S_BAD_MECH;
    }

    tkt_flags = TicketFlags2int(context_handle->ticket->ticket.flags);
    HEIMDAL_MUTEX_unlock(&context_handle->ctx_id_mutex);

    _gsskrb5_encode_om_uint32(tkt_flags, buf);
    value.length = sizeof(buf);
    value.value = buf;

    return gss_add_buffer_set_member(minor_status,
				     &value,
				     data_set);
}
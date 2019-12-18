#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t length; int /*<<< orphan*/ * value; } ;
struct TYPE_5__ {int type; TYPE_1__ buffer; } ;
typedef  TYPE_2__ gss_iov_buffer_desc ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int GSS_IOV_BUFFER_FLAG_ALLOCATED ; 
 int /*<<< orphan*/  GSS_S_COMPLETE ; 
 int /*<<< orphan*/  GSS_S_FAILURE ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 

OM_uint32
_gk_allocate_buffer(OM_uint32 *minor_status, gss_iov_buffer_desc *buffer, size_t size)
{
    if (buffer->type & GSS_IOV_BUFFER_FLAG_ALLOCATED) {
	if (buffer->buffer.length == size)
	    return GSS_S_COMPLETE;
	free(buffer->buffer.value);
    }

    buffer->buffer.value = malloc(size);
    buffer->buffer.length = size;
    if (buffer->buffer.value == NULL) {
	*minor_status = ENOMEM;
	return GSS_S_FAILURE;
    }
    buffer->type |= GSS_IOV_BUFFER_FLAG_ALLOCATED;

    return GSS_S_COMPLETE;
}
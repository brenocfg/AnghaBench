#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gss_buffer_set_t ;
struct TYPE_6__ {size_t count; struct TYPE_6__* elements; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 TYPE_1__* GSS_C_NO_BUFFER_SET ; 
 scalar_t__ GSS_S_COMPLETE ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  gss_release_buffer (scalar_t__*,TYPE_1__*) ; 

OM_uint32
gss_release_buffer_set(OM_uint32 * minor_status, gss_buffer_set_t *buffer_set)
{
	size_t i;
	OM_uint32 minor;

	*minor_status = 0;

	if (*buffer_set == GSS_C_NO_BUFFER_SET)
		return (GSS_S_COMPLETE);

	for (i = 0; i < (*buffer_set)->count; i++)
		gss_release_buffer(&minor, &((*buffer_set)->elements[i]));

	free((*buffer_set)->elements);

	(*buffer_set)->elements = NULL;
	(*buffer_set)->count = 0;

	free(*buffer_set);
	*buffer_set = GSS_C_NO_BUFFER_SET;

	return (GSS_S_COMPLETE);
}
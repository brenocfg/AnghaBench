#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vm_object_t ;
struct uio {scalar_t__ uio_resid; scalar_t__ uio_offset; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 size_t MIN (scalar_t__,scalar_t__) ; 
 int uiomove_object_page (int /*<<< orphan*/ ,size_t,struct uio*) ; 

int
uiomove_object(vm_object_t obj, off_t obj_size, struct uio *uio)
{
	ssize_t resid;
	size_t len;
	int error;

	error = 0;
	while ((resid = uio->uio_resid) > 0) {
		if (obj_size <= uio->uio_offset)
			break;
		len = MIN(obj_size - uio->uio_offset, resid);
		if (len == 0)
			break;
		error = uiomove_object_page(obj, len, uio);
		if (error != 0 || resid == uio->uio_resid)
			break;
	}
	return (error);
}
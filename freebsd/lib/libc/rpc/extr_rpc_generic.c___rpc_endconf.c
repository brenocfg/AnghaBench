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
struct handle {int /*<<< orphan*/  nhandle; scalar_t__ nflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  endnetconfig (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  endnetpath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct handle*) ; 

void
__rpc_endconf(void *vhandle)
{
	struct handle *handle;

	handle = (struct handle *) vhandle;
	if (handle == NULL) {
		return;
	}
	if (handle->nflag) {
		endnetpath(handle->nhandle);
	} else {
		endnetconfig(handle->nhandle);
	}
	free(handle);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  (* xdrproc_t ) (TYPE_1__*,void*) ;
struct TYPE_5__ {int /*<<< orphan*/  x_op; } ;
typedef  TYPE_1__ XDR ;

/* Variables and functions */
 int /*<<< orphan*/  XDR_FREE ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,void*) ; 

void
xdr_free(xdrproc_t proc, void *objp)
{
	XDR x;
	
	x.x_op = XDR_FREE;
	(*proc)(&x, objp);
}
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
struct malloc_type {int dummy; } ;
struct fw_xfer {int tl; struct malloc_type* malloc; } ;

/* Variables and functions */
 int M_NOWAIT ; 
 int M_ZERO ; 
 struct fw_xfer* malloc (int,struct malloc_type*,int) ; 

struct fw_xfer *
fw_xfer_alloc(struct malloc_type *type)
{
	struct fw_xfer *xfer;

	xfer = malloc(sizeof(struct fw_xfer), type, M_NOWAIT | M_ZERO);
	if (xfer == NULL)
		return xfer;

	xfer->malloc = type;
	xfer->tl = -1;

	return xfer;
}
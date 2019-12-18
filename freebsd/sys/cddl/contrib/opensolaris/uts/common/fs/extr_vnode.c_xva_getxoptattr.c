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
struct TYPE_4__ {int va_mask; } ;
struct TYPE_5__ {int /*<<< orphan*/  xva_xoptattrs; TYPE_1__ xva_vattr; } ;
typedef  TYPE_2__ xvattr_t ;
typedef  int /*<<< orphan*/  xoptattr_t ;

/* Variables and functions */
 int AT_XVATTR ; 

xoptattr_t *
xva_getxoptattr(xvattr_t *xvap)
{
	xoptattr_t *xoap = NULL;
	if (xvap->xva_vattr.va_mask & AT_XVATTR)
		xoap = &xvap->xva_xoptattrs;
	return (xoap);
}
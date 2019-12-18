#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_3__ {void* TypeSignature; void* OSSignature; int /*<<< orphan*/  Signature; } ;
typedef  TYPE_1__ uiControl ;

/* Variables and functions */
 scalar_t__ uiprivAlloc (size_t,char const*) ; 
 int /*<<< orphan*/  uiprivControlSignature ; 

uiControl *uiAllocControl(size_t size, uint32_t OSsig, uint32_t typesig, const char *typenamestr)
{
	uiControl *c;

	c = (uiControl *) uiprivAlloc(size, typenamestr);
	c->Signature = uiprivControlSignature;
	c->OSSignature = OSsig;
	c->TypeSignature = typesig;
	return c;
}
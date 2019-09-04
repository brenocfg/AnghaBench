#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {double r; double g; double b; double a; } ;
struct TYPE_6__ {TYPE_2__ color; } ;
struct TYPE_8__ {TYPE_1__ u; } ;
typedef  TYPE_3__ uiAttribute ;

/* Variables and functions */
 TYPE_3__* newAttribute (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiAttributeTypeBackground ; 

uiAttribute *uiNewBackgroundAttribute(double r, double g, double b, double a)
{
	uiAttribute *at;

	at = newAttribute(uiAttributeTypeBackground);
	at->u.color.r = r;
	at->u.color.g = g;
	at->u.color.b = b;
	at->u.color.a = a;
	return at;
}
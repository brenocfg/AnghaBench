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
typedef  int /*<<< orphan*/  uiUnderlineColor ;
struct TYPE_6__ {int /*<<< orphan*/  underlineColor; } ;
struct TYPE_7__ {TYPE_1__ color; } ;
struct TYPE_8__ {TYPE_2__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ uiAttribute ;

/* Variables and functions */
 int /*<<< orphan*/  uiAttributeTypeUnderlineColor ; 
 TYPE_3__* uiNewColorAttribute (double,double,double,double) ; 

uiAttribute *uiNewUnderlineColorAttribute(uiUnderlineColor u, double r, double g, double b, double a)
{
	uiAttribute *at;

	at = uiNewColorAttribute(r, g, b, a);
	at->type = uiAttributeTypeUnderlineColor;
	at->u.color.underlineColor = u;
	return at;
}
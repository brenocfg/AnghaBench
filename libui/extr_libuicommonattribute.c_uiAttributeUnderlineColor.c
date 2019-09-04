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
struct TYPE_8__ {TYPE_2__ u; } ;
typedef  TYPE_3__ uiAttribute ;

/* Variables and functions */
 int /*<<< orphan*/  uiAttributeColor (TYPE_3__ const*,double*,double*,double*,double*) ; 

void uiAttributeUnderlineColor(const uiAttribute *a, uiUnderlineColor *u, double *r, double *g, double *b, double *alpha)
{
	*u = a->u.color.underlineColor;
	uiAttributeColor(a, r, g, b, alpha);
}
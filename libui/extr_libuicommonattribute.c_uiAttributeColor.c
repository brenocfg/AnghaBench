#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {double r; double g; double b; double a; } ;
struct TYPE_6__ {TYPE_1__ color; } ;
struct TYPE_7__ {TYPE_2__ u; } ;
typedef  TYPE_3__ uiAttribute ;

/* Variables and functions */

void uiAttributeColor(const uiAttribute *a, double *r, double *g, double *b, double *alpha)
{
	*r = a->u.color.r;
	*g = a->u.color.g;
	*b = a->u.color.b;
	*alpha = a->u.color.a;
}
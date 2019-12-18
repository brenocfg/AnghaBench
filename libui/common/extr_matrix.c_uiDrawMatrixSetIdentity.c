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
struct TYPE_3__ {int M11; int M22; scalar_t__ M32; scalar_t__ M31; scalar_t__ M21; scalar_t__ M12; } ;
typedef  TYPE_1__ uiDrawMatrix ;

/* Variables and functions */

void uiDrawMatrixSetIdentity(uiDrawMatrix *m)
{
	m->M11 = 1;
	m->M12 = 0;
	m->M21 = 0;
	m->M22 = 1;
	m->M31 = 0;
	m->M32 = 0;
}
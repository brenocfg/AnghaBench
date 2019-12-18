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
struct TYPE_3__ {int numpoints; float** p; } ;
typedef  TYPE_1__ winding_t ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  draw_socket ; 
 int /*<<< orphan*/  send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void GLS_Winding (winding_t *w, int code)
{
	byte	buf[1024];
	int		i, j;

	if (!draw_socket)
		return;

	((int *)buf)[0] = w->numpoints;
	((int *)buf)[1] = code;
	for (i=0 ; i<w->numpoints ; i++)
		for (j=0 ; j<3 ; j++)
			((float *)buf)[2+i*3+j] = w->p[i][j];

	send (draw_socket, buf, w->numpoints*12+8, 0);
}
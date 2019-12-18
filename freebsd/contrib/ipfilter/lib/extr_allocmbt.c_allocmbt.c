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
struct TYPE_3__ {size_t mb_len; char* mb_data; scalar_t__ mb_buf; int /*<<< orphan*/ * mb_next; } ;
typedef  TYPE_1__ mb_t ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 

mb_t *allocmbt(size_t len)
{
	mb_t *m;

	m = (mb_t *)malloc(sizeof(mb_t));
	if (m == NULL)
		return NULL;
	m->mb_len = len;
	m->mb_next = NULL;
	m->mb_data = (char *)m->mb_buf;
	return m;
}
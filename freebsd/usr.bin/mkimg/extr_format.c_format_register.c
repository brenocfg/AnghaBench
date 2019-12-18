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
struct mkimg_format {struct mkimg_format* next; } ;

/* Variables and functions */
 struct mkimg_format* first ; 

void
format_register(struct mkimg_format *f)
{

	f->next = first;
	first = f;
}
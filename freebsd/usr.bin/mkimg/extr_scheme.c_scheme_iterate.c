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
struct mkimg_scheme {struct mkimg_scheme* next; } ;

/* Variables and functions */
 struct mkimg_scheme* first ; 

struct mkimg_scheme *
scheme_iterate(struct mkimg_scheme *s)
{

	return ((s == NULL) ? first : s->next);
}
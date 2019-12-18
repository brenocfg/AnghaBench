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
struct xlocale_monetary {struct xlocale_monetary* buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct xlocale_monetary*) ; 

__attribute__((used)) static void
destruct_monetary(void *v)
{
	struct xlocale_monetary *l = v;
	if (l->buffer)
		free(l->buffer);
	free(l);
}
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
struct html {int /*<<< orphan*/ * tblt; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_tagq (struct html*,int /*<<< orphan*/ *) ; 

void
print_tblclose(struct html *h)
{

	assert(h->tblt);
	print_tagq(h, h->tblt);
	h->tblt = NULL;
}
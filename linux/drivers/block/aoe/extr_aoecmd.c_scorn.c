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
struct aoetgt {int taint; } ;

/* Variables and functions */
 int MAX_TAINT ; 

__attribute__((used)) static void
scorn(struct aoetgt *t)
{
	int n;

	n = t->taint++;
	t->taint += t->taint * 2;
	if (n > t->taint)
		t->taint = n;
	if (t->taint > MAX_TAINT)
		t->taint = MAX_TAINT;
}
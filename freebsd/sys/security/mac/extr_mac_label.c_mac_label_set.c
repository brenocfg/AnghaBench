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
struct label {intptr_t* l_perpolicy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 

void
mac_label_set(struct label *l, int slot, intptr_t v)
{

	KASSERT(l != NULL, ("mac_label_set: NULL label"));

	l->l_perpolicy[slot] = v;
}
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
struct ppc440spe_rxor {int state; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct ppc440spe_rxor*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ppc440spe_init_rxor_cursor(struct ppc440spe_rxor *cursor)
{
	memset(cursor, 0, sizeof(struct ppc440spe_rxor));
	cursor->state = 2;
}
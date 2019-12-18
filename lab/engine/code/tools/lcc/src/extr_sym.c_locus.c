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
typedef  int /*<<< orphan*/  Table ;
typedef  int /*<<< orphan*/  Coordinate ;

/* Variables and functions */
 int /*<<< orphan*/ * allsymbols (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loci ; 
 int /*<<< orphan*/  symbols ; 

void locus(Table tp, Coordinate *cp) {
	loci    = append(cp, loci);
	symbols = append(allsymbols(tp), symbols);
}
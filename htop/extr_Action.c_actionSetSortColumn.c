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
typedef  int /*<<< orphan*/  State ;
typedef  int /*<<< orphan*/  Htop_Reaction ;

/* Variables and functions */
 int /*<<< orphan*/  sortBy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static Htop_Reaction actionSetSortColumn(State* st) {
   return sortBy(st);
}
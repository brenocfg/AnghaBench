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
typedef  int /*<<< orphan*/  Tree ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int) ; 
 int where ; 

Tree texpr(Tree (*f)(int), int tok, int a) {
	int save = where;
	Tree p;

	where = a;
	p = (*f)(tok);
	where = save;
	return p;
}
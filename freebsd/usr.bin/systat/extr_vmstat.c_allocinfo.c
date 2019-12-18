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
struct Info {long* intrcnt; } ;

/* Variables and functions */
 scalar_t__ calloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  nintr ; 

__attribute__((used)) static void
allocinfo(struct Info *ls)
{

	ls->intrcnt = (long *) calloc(nintr, sizeof(long));
	if (ls->intrcnt == NULL)
		errx(2, "out of memory");
}
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
struct foo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,struct foo*) ; 

int
main(void) {

	struct foo *f = 0;
	printf("%p\n", &f[1]);
	return 0;
}
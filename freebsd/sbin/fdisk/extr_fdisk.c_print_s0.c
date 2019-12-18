#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * parts; } ;

/* Variables and functions */
 int NDOSPART ; 
 TYPE_1__ mboot ; 
 int /*<<< orphan*/  print_params () ; 
 int /*<<< orphan*/  print_part (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
print_s0(void)
{
	int	i;

	print_params();
	printf("Information from DOS bootblock is:\n");
	for (i = 1; i <= NDOSPART; i++) {
		printf("%d: ", i);
		print_part(&mboot.parts[i - 1]);
	}
}
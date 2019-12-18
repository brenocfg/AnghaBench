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

/* Variables and functions */
 int /*<<< orphan*/  PORTRANGE_FIRST ; 
 int /*<<< orphan*/  PORTRANGE_LAST ; 
 int get_int_via_sysctlbyname (int /*<<< orphan*/ ) ; 
 int portrange_first ; 
 int portrange_last ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int rand () ; 
 int /*<<< orphan*/  srand (unsigned int) ; 

__attribute__((used)) static int
generate_random_port(int seed)
{
	int random_port;

	printf("Generating a random port with seed=%d\n", seed);
	if (portrange_first == 0) {
		portrange_first = get_int_via_sysctlbyname(PORTRANGE_FIRST);
		printf("Port range lower bound: %d\n", portrange_first);
	}

	if (portrange_last == 0) {
		portrange_last = get_int_via_sysctlbyname(PORTRANGE_LAST);
		printf("Port range upper bound: %d\n", portrange_last);
	}

	srand((unsigned)seed);

	random_port = rand() % (portrange_last - portrange_first) +
	    portrange_first;

	printf("Random port generated: %d\n", random_port);
	return (random_port);
}
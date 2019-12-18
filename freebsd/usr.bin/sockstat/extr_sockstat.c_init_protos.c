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
 int /*<<< orphan*/  endprotoent () ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/ * getprotoent () ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int numprotos ; 
 int /*<<< orphan*/ * protos ; 

__attribute__((used)) static void
init_protos(int num)
{
	int proto_count = 0;

	if (num > 0) {
		proto_count = num;
	} else {
		/* Find the maximum number of possible protocols. */
		while (getprotoent() != NULL)
			proto_count++;
		endprotoent();
	}

	if ((protos = malloc(sizeof(int) * proto_count)) == NULL)
		err(1, "malloc");
	numprotos = proto_count;
}
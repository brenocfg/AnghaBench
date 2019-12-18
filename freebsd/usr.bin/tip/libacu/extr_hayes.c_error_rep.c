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
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
error_rep(char c)
{
	printf("\n\r");
	switch (c) {

	case '0':
		printf("OK");
		break;

	case '1':
		printf("CONNECT");
		break;

	case '2':
		printf("RING");
		break;

	case '3':
		printf("NO CARRIER");
		break;

	case '4':
		printf("ERROR in input");
		break;

	case '5':
		printf("CONNECT 1200");
		break;

	default:
		printf("Unknown Modem error: %c (0x%x)", c, c);
	}
	printf("\n\r");
	return;
}
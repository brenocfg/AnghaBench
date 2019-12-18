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
#define  CANY 130 
#define  CRCV 129 
#define  CSEND 128 
 int cond ; 
 int /*<<< orphan*/  printf (char*) ; 

int
elsecmd(void)
{

	switch (cond) {
	case CANY:
		printf("\"Else\" without matching \"if\"\n");
		return (1);

	case CSEND:
		cond = CRCV;
		break;

	case CRCV:
		cond = CSEND;
		break;

	default:
		printf("Mail's idea of conditions is screwed up\n");
		cond = CANY;
		break;
	}
	return (0);
}
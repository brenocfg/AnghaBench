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
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

int
main(
	int argc,
	char *argv[]
	)
{
	int i;
	int big;
	union {
		unsigned long l;
		char c[sizeof(long)];
	} u;

#if defined(LONG8)
	u.l = (((long)0x08070605) << 32) | (long)0x04030201;
#else
	u.l = 0x04030201;
#endif
	if (sizeof(long) > 4) {
		if (u.c[0] == 0x08) big = 1;
		else		    big = 0;
	} else {
		if (u.c[0] == 0x04) big = 1;
		else		    big = 0;
	}
	for (i=0; i< sizeof(long); i++) {
		if (big == 1 && (u.c[i] == (sizeof(long) - i))) { 
			continue; 
		} else if (big == 0 && (u.c[i] == (i+1))) {
			continue;
		} else {
			big = -1;
			break;
		}
	}

	if (big == 1) {
		printf("XNTP_BIG_ENDIAN\n");
	} else if (big == 0) {
		printf("XNTP_LITTLE_ENDIAN\n");
	}
	exit(0);
}
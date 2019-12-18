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
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int OS_REG_READ (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ah ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,scalar_t__,int,...) ; 

__attribute__((used)) static void
ath_hal_dumprange(FILE *fd, u_int a, u_int b)
{
	u_int r;

	for (r = a; r+16 <= b; r += 5*4)
		fprintf(fd,
			"%04x %08x  %04x %08x  %04x %08x  %04x %08x  %04x %08x\n"
			, r, OS_REG_READ(ah, r)
			, r+4, OS_REG_READ(ah, r+4)
			, r+8, OS_REG_READ(ah, r+8)
			, r+12, OS_REG_READ(ah, r+12)
			, r+16, OS_REG_READ(ah, r+16)
		);
	switch (b-r) {
	case 16:
		fprintf(fd
			, "%04x %08x  %04x %08x  %04x %08x  %04x %08x\n"
			, r, OS_REG_READ(ah, r)
			, r+4, OS_REG_READ(ah, r+4)
			, r+8, OS_REG_READ(ah, r+8)
			, r+12, OS_REG_READ(ah, r+12)
		);
		break;
	case 12:
		fprintf(fd, "%04x %08x  %04x %08x  %04x %08x\n"
			, r, OS_REG_READ(ah, r)
			, r+4, OS_REG_READ(ah, r+4)
			, r+8, OS_REG_READ(ah, r+8)
		);
		break;
	case 8:
		fprintf(fd, "%04x %08x  %04x %08x\n"
			, r, OS_REG_READ(ah, r)
			, r+4, OS_REG_READ(ah, r+4)
		);
		break;
	case 4:
		fprintf(fd, "%04x %08x\n"
			, r, OS_REG_READ(ah, r)
		);
		break;
	}
}
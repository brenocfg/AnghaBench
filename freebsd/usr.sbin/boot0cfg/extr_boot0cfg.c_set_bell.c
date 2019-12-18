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
typedef  unsigned int u_int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static int
set_bell(u_int8_t *mbr, int new_bell, int report)
{
    /* lookup sequence: 0x100 means skip, 0x200 means done */
    static unsigned seq[] =
		{ 0xb0, 0x100, 0xe8, 0x100, 0x100, 0x30, 0xe4, 0x200 };
    int ofs, i, c;
    for (ofs = 0x60; ofs < 0x180; ofs++) { /* search range */
	if (mbr[ofs] != seq[0])	/* search initial pattern */
	    continue;
	for (i=0;; i++) {
	    if (seq[i] == 0x200) {	/* found */
		c = mbr[ofs+1];
		if (!report)
		    mbr[ofs+1] = c = new_bell;
		else
		    printf("  bell=%c (0x%x)",
			(c >= ' ' && c < 0x7f) ? c : ' ', c);
		return c;
	    }
	    if (seq[i] != 0x100 && seq[i] != mbr[ofs+i])
		break;
	}
    }
    warn("bell not found");
    return -1;
}
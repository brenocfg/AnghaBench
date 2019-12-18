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
typedef  int UWORD ;
typedef  int /*<<< orphan*/  UBYTE ;

/* Variables and functions */
 int SIZE ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void main(void)
{
    UBYTE *area, *ptr;
    UWORD i;

    area = malloc(SIZE);
    
    /* Write one bit pattern... */
    memset(area, 0x55U, SIZE);

    /* And another... */
    memset(area, 0xAAU, SIZE);

    /* See if it worked */
    ptr = area;
    for (i=0; i<SIZE; i++) {
	if (*(ptr++) != 0xAAU) {
	    printf("Failed at offset %lx\n", i);
	}
	if (!((UBYTE)i)) {
	    printf("At %lx\r", i);
	}
    }

    /* Dump around the end */
    ptr = area + SIZE - 16;
    printf("\nAt end: \n");
    for (i=0; i<32; i++) {
	printf("%lx: %x\n", (UWORD)((UWORD)&ptr[i] - (UWORD)area - SIZE), ptr[i]);
    }
    printf("\n");
}
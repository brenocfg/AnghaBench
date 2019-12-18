#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int xbe_flags; scalar_t__ xbe_version; char* xbe_name; char* xbe_interpreter; int xbe_msize; int xbe_moffset; int* xbe_magic; int* xbe_mask; } ;
typedef  TYPE_1__ ximgact_binmisc_entry_t ;
typedef  int uint32_t ;

/* Variables and functions */
 scalar_t__ IBE_VERSION ; 
 int IBF_ENABLED ; 
 int IBF_USE_MASK ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
printxbe(ximgact_binmisc_entry_t *xbe)
{
	uint32_t i, flags = xbe->xbe_flags;

	if (xbe->xbe_version != IBE_VERSION) {
		fprintf(stderr, "Error: XBE version mismatch\n");
		return;
	}

	printf("name: %s\n", xbe->xbe_name);
	printf("interpreter: %s\n", xbe->xbe_interpreter);
	printf("flags: %s%s\n", (flags & IBF_ENABLED) ? "ENABLED " : "",
	    (flags & IBF_USE_MASK) ? "USE_MASK " : "");
	printf("magic size: %u\n", xbe->xbe_msize);
	printf("magic offset: %u\n", xbe->xbe_moffset);

	printf("magic: ");
	for(i = 0; i < xbe->xbe_msize;  i++) {
		if (i && !(i % 12))
			printf("\n       ");
		else
			if (i && !(i % 4))
				printf(" ");
		printf("0x%02x ", xbe->xbe_magic[i]);
	}
	printf("\n");

	if (flags & IBF_USE_MASK) {
		printf("mask:  ");
		for(i = 0; i < xbe->xbe_msize;  i++) {
			if (i && !(i % 12))
				printf("\n       ");
			else
				if (i && !(i % 4))
					printf(" ");
			printf("0x%02x ", xbe->xbe_mask[i]);
		}
		printf("\n");
	}

	printf("\n");
}
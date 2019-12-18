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
typedef  int uint8_t ;
struct libusb20_me_struct {int dummy; } ;

/* Variables and functions */
 int* libusb20_desc_foreach (struct libusb20_me_struct*,int const*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
dump_extra(struct libusb20_me_struct *str, const char *plevel)
{
	const uint8_t *ptr;
	uint8_t x;

	ptr = NULL;

	while ((ptr = libusb20_desc_foreach(str, ptr))) {
		printf("\n" "%sAdditional Descriptor\n\n", plevel);
		printf("%sbLength = 0x%02x\n", plevel, ptr[0]);
		printf("%sbDescriptorType = 0x%02x\n", plevel, ptr[1]);
		if (ptr[0] > 1)
			printf("%sbDescriptorSubType = 0x%02x\n",
			    plevel, ptr[2]);
		printf("%s RAW dump: ", plevel);
		for (x = 0; x != ptr[0]; x++) {
			if ((x % 8) == 0) {
				printf("\n%s 0x%02x | ", plevel, x);
			}
			printf("0x%02x%s", ptr[x],
			    (x != (ptr[0] - 1)) ? ", " : (x % 8) ? "\n" : "");
		}
		printf("\n");
	}
	return;
}
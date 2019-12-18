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
typedef  int /*<<< orphan*/  stripe ;
typedef  int U32 ;

/* Variables and functions */
 int /*<<< orphan*/  format_stripe (char*,int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
display_stripe_map(const char *label, U32 StripeMap)
{
	char stripe[5];
	int comma, i;

	comma = 0;
	printf("%s: ", label);
	for (i = 0; StripeMap != 0; i++, StripeMap >>= 1)
		if (StripeMap & 1) {
			format_stripe(stripe, sizeof(stripe), 1 << i);
			if (comma)
				printf(", ");
			printf("%s", stripe);
			comma = 1;
		}
	printf("\n");
}
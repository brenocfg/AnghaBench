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
typedef  int uint32_t ;

/* Variables and functions */
 int magnitude (int const) ; 
 int /*<<< orphan*/  printf (char*,int const) ; 

__attribute__((used)) static void
format(const uint32_t data)
{

  /* XXX: could be simpler, something like this but with leading 0s?

	printf("0x%.*X", magnitude(data), data);
  */

	switch (magnitude(data)) {
	default:
	case 2:
		printf("0x%04X", data);
		break;
	case 3:
		printf("0x%06X", data);
		break;
	case 4:
		printf("0x%08X", data);
		break;
        }
}
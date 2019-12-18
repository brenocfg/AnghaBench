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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  abort2 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void
print_integer(FILE *fp, int val, int base)
{

	switch (base) {
	case 8:
		fprintf(fp, "0%o", val);
		break;
	case 10:
		fprintf(fp, "%d", val);
		break;
	case 16:
		fprintf(fp, "0x%x", val);
		break;
	default:
		abort2("bad base", 0, NULL);
		break;
	}
}
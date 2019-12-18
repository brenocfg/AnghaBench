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
struct keyent_t {int spcl; int* map; int flgs; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int NUM_STATES ; 
 int SPECIAL ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ hex ; 
 int /*<<< orphan*/  print_entry (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
print_key_definition_line(FILE *fp, int scancode, struct keyent_t *key)
{
	int i;

	/* print scancode number */
	if (hex)
		fprintf(fp, " 0x%02x  ", scancode);
	else
		fprintf(fp, "  %03d  ", scancode);

	/* print key definitions */
	for (i=0; i<NUM_STATES; i++) {
		if (key->spcl & (0x80 >> i))
			print_entry(fp, key->map[i] | SPECIAL);
		else
			print_entry(fp, key->map[i]);
	}

	/* print lock state key def */
	switch (key->flgs) {
	case 0:
		fprintf(fp, "  O\n");
		break;
	case 1:
		fprintf(fp, "  C\n");
		break;
	case 2:
		fprintf(fp, "  N\n");
		break;
	case 3:
		fprintf(fp, "  B\n");
		break;
	}
}
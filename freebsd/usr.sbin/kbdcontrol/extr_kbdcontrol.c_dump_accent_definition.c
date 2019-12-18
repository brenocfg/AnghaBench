#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int n_accs; TYPE_1__* acc; } ;
typedef  TYPE_2__ accentmap_t ;
struct TYPE_4__ {int accchar; int** map; } ;

/* Variables and functions */
 int NUM_ACCENTCHARS ; 
 int NUM_DEADKEYS ; 
 char** acc_names ; 
 scalar_t__ isascii (int) ; 
 scalar_t__ isprint (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
dump_accent_definition(char *name, accentmap_t *accentmap)
{
	int i, j;
	int c;

	printf("static accentmap_t accentmap_%s = { %d",
		name, accentmap->n_accs); 
	if (accentmap->n_accs <= 0) {
		printf(" };\n\n");
		return;
	}
	printf(", {\n");
	for (i = 0; i < NUM_DEADKEYS; i++) {
		printf("    /* %s=%d */\n    {", acc_names[i], i);
		c = accentmap->acc[i].accchar;
		if (c == '\'')
			printf(" '\\'', {");
		else if (c == '\\')
			printf(" '\\\\', {");
		else if (isascii(c) && isprint(c))
			printf("  '%c', {", c);
		else if (c == 0) {
			printf(" 0x00 }, \n");
			continue;
		} else
			printf(" 0x%02x, {", c);
		for (j = 0; j < NUM_ACCENTCHARS; j++) {
			c = accentmap->acc[i].map[j][0]; 
			if (c == 0)
				break;
			if ((j > 0) && ((j % 4) == 0))
				printf("\n\t     ");
			if (isascii(c) && isprint(c))
				printf(" {  '%c',", c);
			else
				printf(" { 0x%02x,", c); 
			printf("0x%02x },", accentmap->acc[i].map[j][1]);
		}
		printf(" }, },\n");
	}
	printf("} };\n\n");
}
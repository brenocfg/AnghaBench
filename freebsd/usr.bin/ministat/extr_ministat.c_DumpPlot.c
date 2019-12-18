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
struct plot {scalar_t__ span; int width; int height; int* data; int num_datasets; int** bar; } ;

/* Variables and functions */
 int MAX_DS ; 
 struct plot plot ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 char* symbol ; 

__attribute__((used)) static void
DumpPlot(void)
{
	struct plot *pl;
	int i, j, k;

	pl = &plot;
	if (pl->span == 0) {
		printf("[no plot, span is zero width]\n");
		return;
	}

	putchar('+');
	for (i = 0; i < pl->width; i++)
		putchar('-');
	putchar('+');
	putchar('\n');
	for (i = 1; i < pl->height; i++) {
		putchar('|');
		for (j = 0; j < pl->width; j++) {
			k = pl->data[(pl->height - i) * pl->width + j];
			if (k >= 0 && k < MAX_DS)
				putchar(symbol[k]);
			else
				printf("[%02x]", k);
		}
		putchar('|');
		putchar('\n');
	}
	for (i = 0; i < pl->num_datasets; i++) {
		if (pl->bar[i] == NULL)
			continue;
		putchar('|');
		for (j = 0; j < pl->width; j++) {
			k = pl->bar[i][j];
			if (k == 0)
				k = ' ';
			putchar(k);
		}
		putchar('|');
		putchar('\n');
	}
	putchar('+');
	for (i = 0; i < pl->width; i++)
		putchar('-');
	putchar('+');
	putchar('\n');
}
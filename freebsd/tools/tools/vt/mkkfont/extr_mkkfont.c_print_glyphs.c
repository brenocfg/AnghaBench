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
typedef  int /*<<< orphan*/  uint8_t ;
struct file_header {unsigned int height; int /*<<< orphan*/  glyph_count; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 unsigned int be32toh (int /*<<< orphan*/ ) ; 
 int fread (int /*<<< orphan*/ *,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 unsigned int howmany (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * malloc (unsigned int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdin ; 

__attribute__((used)) static int
print_glyphs(struct file_header *fh)
{
	unsigned int gbytes, glyph_count, j, k, total;
	uint8_t *gbuf;

	gbytes = howmany(fh->width, 8) * fh->height;
	glyph_count = be32toh(fh->glyph_count);

	printf("\nstatic uint8_t font_bytes[%u * %u] = {", glyph_count, gbytes);
	total = glyph_count * gbytes;
	gbuf = malloc(total);

	if (fread(gbuf, total, 1, stdin) != 1) {
		perror("glyph");
		return (1);
	}

	for (j = 0; j < total; j += 12) {
		for (k = 0; k < 12 && k < total - j; k++) {
			printf(k == 0 ? "\n\t" : " ");
			printf("0x%02hhx,", gbuf[j + k]);
		}
	}

	free(gbuf);
	printf("\n};\n");

	return (0);
}
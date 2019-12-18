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
struct file_mapping {int /*<<< orphan*/  length; int /*<<< orphan*/  destination; int /*<<< orphan*/  source; } ;
struct file_header {int /*<<< orphan*/ * map_count; } ;

/* Variables and functions */
 int be16toh (int /*<<< orphan*/ ) ; 
 int be32toh (int /*<<< orphan*/ ) ; 
 int fread (struct file_mapping*,int,int,int /*<<< orphan*/ ) ; 
 char** map_names ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdin ; 

__attribute__((used)) static int
print_mappings(struct file_header *fh, int map_index)
{
	struct file_mapping fm;
	unsigned int nmappings, i, col = 0;

	
	nmappings = be32toh(fh->map_count[map_index]);

	if (nmappings == 0)
		return (0);

	printf("\nstatic struct vt_font_map font_mapping_%s[%u] = {",
	    map_names[map_index], nmappings);

	for (i = 0; i < nmappings; i++) {
		if (fread(&fm, sizeof fm, 1, stdin) != 1) {
			perror("mapping");
			return (1);
		}

		printf(col == 0 ? "\n\t" : " ");
		printf("{ 0x%04x, 0x%04x, 0x%02x },",
		    be32toh(fm.source), be16toh(fm.destination),
		    be16toh(fm.length));
		col = (col + 1) % 2;
	}

	printf("\n};\n");

	return (0);
}
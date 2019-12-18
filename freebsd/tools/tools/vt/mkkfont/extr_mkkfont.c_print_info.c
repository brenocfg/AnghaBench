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
struct file_header {int width; int height; scalar_t__* map_count; } ;

/* Variables and functions */
 int be32toh (scalar_t__) ; 
 char** map_names ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
print_info(struct file_header *fh)
{
	unsigned int i;

	printf(
	    "\nstruct vt_font vt_font_default = {\n"
	    "\t.vf_width\t\t= %u,\n"
	    "\t.vf_height\t\t= %u,\n"
	    "\t.vf_bytes\t\t= font_bytes,\n",
	    fh->width, fh->height);

	printf("\t.vf_map\t\t\t= {\n");
	for (i = 0; i < 4; i++) {
		if (fh->map_count[i] > 0)
			printf("\t\t\t\t    font_mapping_%s,\n", map_names[i]);
		else
			printf("\t\t\t\t    NULL,\n");
	}
	printf("\t\t\t\t  },\n");
	printf("\t.vf_map_count\t\t= { %u, %u, %u, %u },\n",
	    be32toh(fh->map_count[0]),
	    be32toh(fh->map_count[1]),
	    be32toh(fh->map_count[2]),
	    be32toh(fh->map_count[3]));
	printf("\t.vf_refcount\t\t= 1,\n};\n");

	return (0);
}
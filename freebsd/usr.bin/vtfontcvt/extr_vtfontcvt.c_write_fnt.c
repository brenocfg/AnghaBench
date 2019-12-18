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
struct file_header {char* magic; void** map_count; void* glyph_count; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  VFNT_MAP_BOLD ; 
 int /*<<< orphan*/  VFNT_MAP_BOLD_RH ; 
 int /*<<< orphan*/  VFNT_MAP_NORMAL ; 
 int /*<<< orphan*/  VFNT_MAP_NORMAL_RH ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int fwrite (struct file_header*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glyph_unique ; 
 int /*<<< orphan*/  height ; 
 void* htobe32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * map_folded_count ; 
 int /*<<< orphan*/  perror (char const*) ; 
 int /*<<< orphan*/  width ; 
 scalar_t__ write_glyphs (int /*<<< orphan*/ *) ; 
 scalar_t__ write_mappings (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
write_fnt(const char *filename)
{
	FILE *fp;
	struct file_header fh = {
		.magic = "VFNT0002",
	};

	fp = fopen(filename, "wb");
	if (fp == NULL) {
		perror(filename);
		return (1);
	}

	fh.width = width;
	fh.height = height;
	fh.glyph_count = htobe32(glyph_unique);
	fh.map_count[0] = htobe32(map_folded_count[0]);
	fh.map_count[1] = htobe32(map_folded_count[1]);
	fh.map_count[2] = htobe32(map_folded_count[2]);
	fh.map_count[3] = htobe32(map_folded_count[3]);
	if (fwrite(&fh, sizeof fh, 1, fp) != 1) {
		perror(filename);
		fclose(fp);
		return (1);
	}

	if (write_glyphs(fp) != 0 ||
	    write_mappings(fp, VFNT_MAP_NORMAL) != 0 ||
	    write_mappings(fp, VFNT_MAP_NORMAL_RH) != 0 ||
	    write_mappings(fp, VFNT_MAP_BOLD) != 0 ||
	    write_mappings(fp, VFNT_MAP_BOLD_RH) != 0) {
		perror(filename);
		fclose(fp);
		return (1);
	}

	fclose(fp);
	return (0);
}
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
struct file_info {int file_size; int /*<<< orphan*/  file_name; int /*<<< orphan*/  file_data; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,...) ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int fread (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 int ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bufferFile(struct file_info* finfo) {
	int fs = 0;
	FILE* fp = NULL;

	if (!finfo || !finfo->file_name) {
		ERR("Invalid pointer provided!\n");
		return -1;
	}

	DBG("Opening file: %s\n", finfo->file_name);

	if (!(fp = fopen(finfo->file_name, "rb"))) {
		ERR("Error opening file: %s\n", finfo->file_name);
		return -1;
	}

	/* Get filesize */
	rewind(fp);
	fseek(fp, 0L, SEEK_END);
	fs = ftell(fp);
	rewind(fp);

	if (fs < 0) {
		ERR("Error getting filesize: %s\n", finfo->file_name);
		fclose(fp);
		return -1;
	}

	DBG("Filesize: %i\n", fs);
	finfo->file_size = fs;

	if (!(finfo->file_data = malloc(fs))) {
		ERR("Out of memory!\n");
		fclose(fp);
		return -1;
	}

	if (fread(finfo->file_data, 1, fs, fp) != fs) {
		ERR("Error reading file %s\n", finfo->file_name);
		fclose(fp);
		return -1;
	}

	DBG("File: read successful\n");
	fclose(fp);

	return 0;
}
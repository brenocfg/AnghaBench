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
struct file_info {scalar_t__ file_size; int /*<<< orphan*/  file_data; int /*<<< orphan*/  file_name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fwrite (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int writeFile(struct file_info* finfo) {
	FILE* fp;

	if (!finfo || !finfo->file_name) {
		ERR("Invalid pointer provided!\n");
		return -1;
	}

	DBG("Opening file: %s\n", finfo->file_name);

	if (!(fp = fopen(finfo->file_name, "w"))) {
		ERR("Error opening file: %s\n", finfo->file_name);
		return -1;
	}

	DBG("Writing file: %s\n", finfo->file_name);

	if (fwrite(finfo->file_data, 1, finfo->file_size, fp) != finfo->file_size) {
		ERR("Wanted to write, but something went wrong!\n");
		fclose(fp);
		return -1;
	}

	fclose(fp);
	return 0;
}
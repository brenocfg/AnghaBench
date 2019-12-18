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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,char*) ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  VERBOSE (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  buffer ; 
 scalar_t__ config_size ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ fread (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 scalar_t__ ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc (scalar_t__) ; 

__attribute__((used)) static int read_file(char *file_name)
{
	int ret = EXIT_FAILURE;
	uint32_t file_size = 0;
	FILE *fp;

	fp = fopen(file_name, "r");

	if (!fp) {
		ERR("Failed to open config input file %s", file_name);
		goto out;
	}

	fseek(fp, 0L, SEEK_END);
	file_size = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	buffer = malloc(file_size);
	VERBOSE("Allocated %d bytes.", file_size);

	if (fread(buffer, 1, file_size, fp) != file_size) {
		ERR("Failed to read config input file %s", file_name);
		goto out_free_buf;
	}

	VERBOSE("Read %d bytes of config input file %s", file_size, file_name);
	config_size = file_size;
	ret = EXIT_SUCCESS;
	goto out;

 out_free_buf:
	free(buffer);
	fclose(fp);
 out:
	return ret;
}
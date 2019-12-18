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
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t EACCES ; 
 size_t EIO ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 size_t fread (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 size_t fwrite (int /*<<< orphan*/ *,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seama_path ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static ssize_t oseama_entity_append_file(FILE *seama, const char *in_path) {
	FILE *in;
	size_t bytes;
	ssize_t length = 0;
	uint8_t buf[128];

	in = fopen(in_path, "r");
	if (!in) {
		fprintf(stderr, "Couldn't open %s\n", in_path);
		return -EACCES;
	}

	while ((bytes = fread(buf, 1, sizeof(buf), in)) > 0) {
		if (fwrite(buf, 1, bytes, seama) != bytes) {
			fprintf(stderr, "Couldn't write %zu B to %s\n", bytes, seama_path);
			length = -EIO;
			break;
		}
		length += bytes;
	}

	fclose(in);

	return length;
}
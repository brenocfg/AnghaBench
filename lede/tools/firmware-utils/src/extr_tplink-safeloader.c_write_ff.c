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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 

__attribute__((used)) static void write_ff(FILE *output_file, size_t size)
{
	char buf[4096];
	int offset;

	memset(buf, 0xff, sizeof(buf));

	for (offset = 0; offset + sizeof(buf) < size ; offset += sizeof(buf)) {
		if (fwrite(buf, sizeof(buf), 1, output_file) < 0)
			error(1, errno, "Can not write 0xff to output_file");
	}

	/* write last chunk smaller than buffer */
	if (offset < size) {
		offset = size - offset;
		if (fwrite(buf, offset, 1, output_file) < 0)
			error(1, errno, "Can not write partition to output_file");
	}
}
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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int parse_bdf (int /*<<< orphan*/ *,unsigned int) ; 
 int parse_hex (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  perror (char const*) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int
parse_file(const char *filename, unsigned int map_idx)
{
	FILE *fp;
	size_t len;
	int rv;

	fp = fopen(filename, "r");
	if (fp == NULL) {
		perror(filename);
		return (1);
	}
	len = strlen(filename);
	if (len > 4 && strcasecmp(filename + len - 4, ".hex") == 0)
		rv = parse_hex(fp, map_idx);
	else
		rv = parse_bdf(fp, map_idx);
	fclose(fp);
	return (rv);
}
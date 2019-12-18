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
 int EIO ; 
 int fprintf (int /*<<< orphan*/ *,char*,char const*,char const*,char*,char const*) ; 

__attribute__((used)) static int
kvp_write_file(FILE *f, const char *s1, const char *s2, const char *s3)
{
	int ret;

	ret = fprintf(f, "%s%s%s%s\n", s1, s2, "=", s3);

	if (ret < 0) {
		return (EIO);
	}

	return (0);
}
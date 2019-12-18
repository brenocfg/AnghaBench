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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 size_t fread (void*,size_t,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (void*) ; 
 int fseek (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  warn (char*,...) ; 

void *
read_buf(FILE *fp, off_t off, size_t len)
{
	int error;
	size_t nread;
	void *buf;

	error = fseek(fp, off, SEEK_SET);
	if (error != 0) {
		warn("cannot seek to %jd", (uintmax_t)off);
		return (NULL);
	}

	buf = malloc(len);
	if (buf == NULL) {
		warn("cannot malloc %zd bytes of memory", len);
		return (NULL);
	}

	nread = fread(buf, len, 1, fp);
	if (nread != 1) {
		free(buf);
		if (feof(fp) == 0)
			warn("fread");
		return (NULL);
	}

	return (buf);
}
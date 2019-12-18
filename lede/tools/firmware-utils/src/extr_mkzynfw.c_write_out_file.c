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
struct csum_state {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,char*,char*,size_t) ; 
 int /*<<< orphan*/  ERRS (char*,char*) ; 
 int FILE_BUF_LEN ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fread (char*,size_t,int,int /*<<< orphan*/ *) ; 
 int write_out_data (int /*<<< orphan*/ *,char*,size_t,struct csum_state*) ; 

int
write_out_file(FILE *outfile, char *name, size_t len, struct csum_state *css)
{
	char buf[FILE_BUF_LEN];
	size_t buflen = sizeof(buf);
	FILE *f;
	int res;

	DBG(2, "writing out file, name=%s, len=%zu",
		name, len);

	errno = 0;
	f = fopen(name,"r");
	if (errno) {
		ERRS("unable to open file: %s", name);
		return -1;
	}

	while (len > 0) {
		if (len < buflen)
			buflen = len;

		/* read data from source file */
		errno = 0;
		fread(buf, buflen, 1, f);
		if (errno != 0) {
			ERRS("unable to read from file: %s",name);
			res = -1;
			break;
		}

		res = write_out_data(outfile, buf, buflen, css);
		if (res)
			break;

		len -= buflen;
	}

	fclose(f);
	return res;
}
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

/* Variables and functions */
 int GROUPS ; 
 char** av ; 
 int b64_ntop (unsigned char*,size_t,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 size_t fread (unsigned char*,int,int,int /*<<< orphan*/ ) ; 
 int mode ; 
 int /*<<< orphan*/  nitems (char*) ; 
 int /*<<< orphan*/  output ; 
 int /*<<< orphan*/  raw ; 
 int /*<<< orphan*/  stdin ; 

__attribute__((used)) static void
base64_encode(void)
{
	/*
	 * Output must fit into 80 columns, chunks come in 4, leave 1.
	 */
#define	GROUPS	((80 / 4) - 1)
	unsigned char buf[3];
	char buf2[sizeof(buf) * 2 + 1];
	size_t n;
	int rv, sequence;

	sequence = 0;

	if (!raw)
		fprintf(output, "begin-base64 %o %s\n", mode, *av);
	while ((n = fread(buf, 1, sizeof(buf), stdin))) {
		++sequence;
		rv = b64_ntop(buf, n, buf2, nitems(buf2));
		if (rv == -1)
			errx(1, "b64_ntop: error encoding base64");
		fprintf(output, "%s%s", buf2, (sequence % GROUPS) ? "" : "\n");
	}
	if (sequence % GROUPS)
		fprintf(output, "\n");
	if (!raw)
		fprintf(output, "====\n");
}
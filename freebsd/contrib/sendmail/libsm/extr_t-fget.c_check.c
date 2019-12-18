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
typedef  int /*<<< orphan*/  SM_FILE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SM_IO_RDONLY_B ; 
 int /*<<< orphan*/  SM_IO_WRONLY_B ; 
 int /*<<< orphan*/  SM_TEST (int) ; 
 int /*<<< orphan*/  SM_TIME_DEFAULT ; 
 int /*<<< orphan*/  SmFtStdio ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,int,int) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int sm_io_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sm_io_fgets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/ * sm_io_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sm_io_putc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  stderr ; 

void
check(char *msg, int l)
{
	SM_FILE_T *wfp, *rfp;
	char buf[256];
	size_t n;
	int r, i;
	static char fn[] = "tfget";

	wfp = sm_io_open(SmFtStdio, SM_TIME_DEFAULT, fn,
			   SM_IO_WRONLY_B, NULL);
	SM_TEST(wfp != NULL);
	for (i = 0; i < l; i++)
	{
		r = sm_io_putc(wfp, SM_TIME_DEFAULT, msg[i]);
		SM_TEST(r >= 0);
	}
	r = sm_io_close(wfp, SM_TIME_DEFAULT);
	SM_TEST(r == 0);

	rfp = sm_io_open(SmFtStdio, SM_TIME_DEFAULT, fn,
			   SM_IO_RDONLY_B, NULL);
	SM_TEST(rfp != NULL);
	n = sizeof(buf);
	r = sm_io_fgets(rfp, SM_TIME_DEFAULT, buf, n);
	if (l == 0)
	{
		SM_TEST(r == -1);
		SM_TEST(errno == 0);
	}
	else
	{
		SM_TEST(r == l);
		if (r != l)
			fprintf(stderr, "buf='%s', in='%s', r=%d, l=%d\n",
				buf, msg, r, l);
	}
	SM_TEST(memcmp(buf, msg, l) == 0);
	r = sm_io_close(rfp, SM_TIME_DEFAULT);
	SM_TEST(r == 0);
}
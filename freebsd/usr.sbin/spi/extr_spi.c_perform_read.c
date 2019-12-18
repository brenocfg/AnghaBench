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
struct spi_options {int count; int ncmd; int /*<<< orphan*/  lsb; int /*<<< orphan*/  pcmd; } ;

/* Variables and functions */
 int _do_data_output (void*,struct spi_options*) ; 
 int _read_write (int,void*,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (void*,int) ; 
 int /*<<< orphan*/  free (void*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
perform_read(int hdev, struct spi_options *popt)
{
	int icount, err;
	void   *pr, *pw;

	pr = NULL;
	icount = popt->count + popt->ncmd;

	/* prep write buffer filled with 0 bytes */
	pw = malloc(icount);

	if (!pw) {
		err = -1;
		goto the_end;
	}

	bzero(pw, icount);

	/* if I included a command sequence, copy bytes to the write buf */
	if (popt->pcmd && popt->ncmd > 0)
		memcpy(pw, popt->pcmd, popt->ncmd);

	pr = malloc(icount + 1);

	if (!pr) {
		err = -2;
		goto the_end;
	}

	bzero(pr, icount);

	err = _read_write(hdev, pw, pr, icount, popt->lsb);

	if (!err && popt->count > 0)
		err = _do_data_output(pr, popt);

the_end:

	free(pr);
	free(pw);

	return err;
}
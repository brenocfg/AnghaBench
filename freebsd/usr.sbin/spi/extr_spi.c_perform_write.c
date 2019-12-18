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
struct spi_options {int /*<<< orphan*/  lsb; scalar_t__ ncmd; scalar_t__ count; } ;

/* Variables and functions */
 int _read_write (int,void*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 
 void* prep_write_buffer (struct spi_options*) ; 

__attribute__((used)) static int
perform_write(int hdev, struct spi_options *popt)
{
	int err;
	void   *pw;

	/* read data from cmd buf and stdin and write to 'write' buffer */

	pw = prep_write_buffer(popt);

	if (!pw) {
		err = -1;
		goto the_end;
	}

	err = _read_write(hdev, pw, NULL, popt->count + popt->ncmd, popt->lsb);

the_end:

	free(pw);

	return err;
}
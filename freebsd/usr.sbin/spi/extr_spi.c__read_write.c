#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_2__ {int iov_len; void* iov_base; } ;
struct spigen_transfer {TYPE_1__ st_command; } ;
typedef  int /*<<< orphan*/  spi ;

/* Variables and functions */
 int /*<<< orphan*/  SPIGENIOC_TRANSFER ; 
 int /*<<< orphan*/  bzero (struct spigen_transfer*,int) ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct spigen_transfer*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 size_t* reversebits ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
_read_write(int hdev, void *bufw, void *bufr, int cbrw, int lsb)
{
	int	err, ctr;
	struct spigen_transfer spi;

	if (!cbrw)
		return 0;

	if (!bufr)
		bufr = bufw;
	else
		memcpy(bufr, bufw, cbrw);	/* transaction uses bufr for
						 * both R and W */

	bzero(&spi, sizeof(spi));	/* zero structure first */

	/* spigen code seems to suggest there must be at least 1 command byte */

	spi.st_command.iov_base = bufr;
	spi.st_command.iov_len = cbrw;

	/*
	 * The remaining members for spi.st_data are zero - all bytes are
	 * 'command' for this. The driver doesn't really do anything different
	 * for 'command' vs 'data' and at least one command byte must be sent in
	 * the transaction.
	 */

	err = ioctl(hdev, SPIGENIOC_TRANSFER, &spi) < 0 ? -1 : 0;

	if (!err && lsb) {
		/* flip the bits for 'lsb' mode */
		for (ctr = 0; ctr < cbrw; ctr++) {
			((uint8_t *) bufr)[ctr] =
			    reversebits[((uint8_t *)bufr)[ctr]];
		}
	}

	if (err)
		fprintf(stderr, "Error performing SPI transaction, errno=%d\n",
		    errno);

	return err;
}
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
struct aiocb {int aio_fildes; int aio_nbytes; char* aio_buf; int /*<<< orphan*/  aio_offset; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  scalar_t__ iot_t ;

/* Variables and functions */
 scalar_t__ IOT_READ ; 
 int aio_read (struct aiocb*) ; 
 int aio_write (struct aiocb*) ; 
 int /*<<< orphan*/  bzero (struct aiocb*,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 

__attribute__((used)) static void
set_aio(struct aiocb *a, iot_t iot, int fd, off_t offset, int size, char *buf)
{
	int r;
	bzero(a, sizeof(*a));
	a->aio_fildes = fd;
	a->aio_nbytes = size;
	a->aio_offset = offset;
	a->aio_buf = buf;
	if (iot == IOT_READ)
		r = aio_read(a);
	else
		r = aio_write(a);
	if (r != 0)
		err(1, "set_aio call failed");
}
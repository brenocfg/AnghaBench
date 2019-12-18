#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ io_error; int /*<<< orphan*/  io_size; int /*<<< orphan*/  io_abd; int /*<<< orphan*/  io_bp; } ;
typedef  TYPE_1__ zio_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  abd_t ;

/* Variables and functions */
 int /*<<< orphan*/  BP_GET_COMPRESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EIO ; 
 scalar_t__ SET_ERROR (int /*<<< orphan*/ ) ; 
 void* abd_borrow_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abd_return_buf_copy (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int zio_decompress_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
zio_decompress(zio_t *zio, abd_t *data, uint64_t size)
{
	if (zio->io_error == 0) {
		void *tmp = abd_borrow_buf(data, size);
		int ret = zio_decompress_data(BP_GET_COMPRESS(zio->io_bp),
		    zio->io_abd, tmp, zio->io_size, size);
		abd_return_buf_copy(data, tmp, size);

		if (ret != 0)
			zio->io_error = SET_ERROR(EIO);
	}
}
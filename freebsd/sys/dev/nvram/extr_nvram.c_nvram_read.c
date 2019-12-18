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
typedef  int /*<<< orphan*/  u_char ;
struct uio {scalar_t__ uio_resid; int uio_offset; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int NVRAM_FIRST ; 
 int NVRAM_LAST ; 
 int /*<<< orphan*/  rtcin (int) ; 
 int uiomove (int /*<<< orphan*/ *,int,struct uio*) ; 

__attribute__((used)) static int
nvram_read(struct cdev *dev, struct uio *uio, int flags)
{
	int nv_off;
	u_char v;
	int error = 0;

	while (uio->uio_resid > 0 && error == 0) {
		nv_off = uio->uio_offset + NVRAM_FIRST;
		if (nv_off < NVRAM_FIRST || nv_off >= NVRAM_LAST)
			return (0);	/* Signal EOF */
		/* Single byte at a time */
		v = rtcin(nv_off);
		error = uiomove(&v, 1, uio);
	}
	return (error);

}
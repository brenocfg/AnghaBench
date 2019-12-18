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
struct dumperinfo {int blocksize; scalar_t__ blockbuf; } ;

/* Variables and functions */
 int dump_append (struct dumperinfo*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int fragsz ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 

int
dumpsys_buf_write(struct dumperinfo *di, char *ptr, size_t sz)
{
	size_t len;
	int error;

	while (sz) {
		len = di->blocksize - fragsz;
		if (len > sz)
			len = sz;
		memcpy((char *)di->blockbuf + fragsz, ptr, len);
		fragsz += len;
		ptr += len;
		sz -= len;
		if (fragsz == di->blocksize) {
			error = dump_append(di, di->blockbuf, 0, di->blocksize);
			if (error)
				return (error);
			fragsz = 0;
		}
	}
	return (0);
}
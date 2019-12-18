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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct dumperinfo {size_t maxiosize; TYPE_1__* kdcomp; } ;
struct TYPE_2__ {int /*<<< orphan*/  kdc_stream; void* kdc_buf; } ;

/* Variables and functions */
 int EINVAL ; 
 int _dump_append (struct dumperinfo*,void*,int /*<<< orphan*/ ,size_t) ; 
 int compressor_write (int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  memmove (void*,void*,size_t) ; 

int
dump_append(struct dumperinfo *di, void *virtual, vm_offset_t physical,
    size_t length)
{
	void *buf;

	if (di->kdcomp != NULL) {
		/* Bounce through a buffer to avoid CRC errors. */
		if (length > di->maxiosize)
			return (EINVAL);
		buf = di->kdcomp->kdc_buf;
		memmove(buf, virtual, length);
		return (compressor_write(di->kdcomp->kdc_stream, buf, length));
	}
	return (_dump_append(di, virtual, physical, length));
}
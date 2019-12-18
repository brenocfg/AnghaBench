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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct resource {scalar_t__ size; scalar_t__ ofs; void* ptr; int /*<<< orphan*/  fd; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ESPIPE ; 
 void* MAP_FAILED ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct resource* rid_lookup (int) ; 
 scalar_t__ write (int /*<<< orphan*/ ,void*,scalar_t__) ; 

int
bs_write(int rid, off_t ofs, void *buf, ssize_t bufsz)
{
	struct resource *r;
	volatile void *ptr;
	off_t o;
	ssize_t s;

	r = rid_lookup(rid);
	if (r == NULL)
		return (0);
	if (ofs < 0 || ofs > r->size - bufsz) {
		errno = ESPIPE;
		return (0);
	}
	ofs += r->ofs;
	if (r->ptr != MAP_FAILED) {
		ptr = r->ptr + ofs;
		switch (bufsz) {
		case 1:
			*((volatile uint8_t *)ptr) = *((uint8_t *)buf);
			break;
		case 2:
			*((volatile uint16_t *)ptr) = *((uint16_t *)buf);
			break;
		case 4:
			*((volatile uint32_t *)ptr) = *((uint32_t *)buf);
			break;
		default:
			errno = EIO;
			return (0);
		}
	} else {
		o = lseek(r->fd, ofs, SEEK_SET);
		if (o != ofs)
			return (0);
		s = write(r->fd, buf, bufsz);
		if (s != bufsz)
			return (0);
	}
	return (1);
}
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

/* Variables and functions */
 scalar_t__ subyte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ suword32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ suword64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

size_t
linux_clear_user(void *_uaddr, size_t _len)
{
	uint8_t *uaddr = _uaddr;
	size_t len = _len;

	/* make sure uaddr is aligned before going into the fast loop */
	while (((uintptr_t)uaddr & 7) != 0 && len > 7) {
		if (subyte(uaddr, 0))
			return (_len);
		uaddr++;
		len--;
	}

	/* zero 8 bytes at a time */
	while (len > 7) {
#ifdef __LP64__
		if (suword64(uaddr, 0))
			return (_len);
#else
		if (suword32(uaddr, 0))
			return (_len);
		if (suword32(uaddr + 4, 0))
			return (_len);
#endif
		uaddr += 8;
		len -= 8;
	}

	/* zero fill end, if any */
	while (len > 0) {
		if (subyte(uaddr, 0))
			return (_len);
		uaddr++;
		len--;
	}
	return (0);
}
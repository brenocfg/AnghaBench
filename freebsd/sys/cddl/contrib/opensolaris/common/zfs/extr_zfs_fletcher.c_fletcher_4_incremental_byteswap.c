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
struct TYPE_3__ {scalar_t__* zc_word; } ;
typedef  TYPE_1__ zio_cksum_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 scalar_t__ BSWAP_32 (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ZIO_SET_CHECKSUM (TYPE_1__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

int
fletcher_4_incremental_byteswap(void *buf, size_t size, void *data)
{
	zio_cksum_t *zcp = data;

	const uint32_t *ip = buf;
	const uint32_t *ipend = ip + (size / sizeof (uint32_t));
	uint64_t a, b, c, d;

	a = zcp->zc_word[0];
	b = zcp->zc_word[1];
	c = zcp->zc_word[2];
	d = zcp->zc_word[3];

	for (; ip < ipend; ip++) {
		a += BSWAP_32(ip[0]);
		b += a;
		c += b;
		d += c;
	}

	ZIO_SET_CHECKSUM(zcp, a, b, c, d);
	return (0);
}
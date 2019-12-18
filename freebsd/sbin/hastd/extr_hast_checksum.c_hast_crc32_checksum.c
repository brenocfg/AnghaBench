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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  crc ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  crc32 (unsigned char const*,size_t) ; 

__attribute__((used)) static void
hast_crc32_checksum(const unsigned char *data, size_t size,
    unsigned char *hash, size_t *hsizep)
{
	uint32_t crc;

	crc = crc32(data, size);
	/* XXXPJD: Do we have to use htole32() on crc first? */
	bcopy(&crc, hash, sizeof(crc));
	*hsizep = sizeof(crc);
}
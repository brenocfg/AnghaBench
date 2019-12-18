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
struct iso9660 {int /*<<< orphan*/  null; } ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ ,unsigned char const*,unsigned int) ; 

__attribute__((used)) static int
isNull(struct iso9660 *iso9660, const unsigned char *h, unsigned offset,
unsigned bytes)
{

	while (bytes >= sizeof(iso9660->null)) {
		if (!memcmp(iso9660->null, h + offset, sizeof(iso9660->null)))
			return (0);
		offset += sizeof(iso9660->null);
		bytes -= sizeof(iso9660->null);
	}
	if (bytes)
		return memcmp(iso9660->null, h + offset, bytes) == 0;
	else
		return (1);
}
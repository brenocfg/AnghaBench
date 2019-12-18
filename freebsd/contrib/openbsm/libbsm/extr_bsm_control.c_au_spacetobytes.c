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
typedef  int /*<<< orphan*/  u_long ;

/* Variables and functions */

__attribute__((used)) static int
au_spacetobytes(size_t *bytes, u_long value, char mult)
{
	if (NULL == bytes)
		return (-1);

	switch(mult) {
	case 'B':
	case ' ':
		/* Bytes */
		*bytes = (size_t)value;
		break;

	case 'K':
		/* Kilobytes */
		*bytes = (size_t)value * 1024;
		break;

	case 'M':
		/* Megabytes */
		*bytes = (size_t)value * 1024 * 1024;
		break;

	case 'G':
		/* Gigabytes */
		*bytes = (size_t)value * 1024 * 1024 * 1024;
		break;

	default:
		return (-1);
	}
	return (0);
}
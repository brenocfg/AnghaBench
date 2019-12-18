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
typedef  int uintmax_t ;
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int parse_digit (int /*<<< orphan*/  const) ; 

__attribute__((used)) static uintmax_t
parse_integer(const uint8_t *p, size_t len)
{
	uintmax_t v;

	v = 0;
	while (len > 0) {
		v <<= 4;
		v |= parse_digit(*p);
		p++;
		len--;
	}
	return (v);
}
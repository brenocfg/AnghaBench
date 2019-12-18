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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  be64enc (unsigned char*,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void
be64enc_vect(unsigned char *dst, const uint64_t *src, size_t len)
{
	size_t i;

	for (i = 0; i < len / 8; i++)
		be64enc(dst + i * 8, src[i]);
}
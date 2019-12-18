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
struct lz_decoder {int crc; } ;

/* Variables and functions */

__attribute__((used)) static unsigned
lz_get_crc(const struct lz_decoder *lz)
{
	return lz->crc ^ 0xffffffffU;
}
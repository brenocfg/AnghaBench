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

/* Variables and functions */

__attribute__((used)) static unsigned long
decode_codec_id(const unsigned char *codecId, size_t id_size)
{
	unsigned i;
	unsigned long id = 0;

	for (i = 0; i < id_size; i++) {
		id <<= 8;
		id += codecId[i];
	}
	return (id);
}
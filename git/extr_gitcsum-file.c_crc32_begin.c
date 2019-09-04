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
struct hashfile {int do_crc; int /*<<< orphan*/  crc32; } ;

/* Variables and functions */
 int /*<<< orphan*/  crc32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void crc32_begin(struct hashfile *f)
{
	f->crc32 = crc32(0, NULL, 0);
	f->do_crc = 1;
}
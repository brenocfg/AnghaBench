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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int bitoffs; } ;
typedef  TYPE_1__ ib_field_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  ntohll (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t _get_field64(void *buf, int base_offs, const ib_field_t * f)
{
	uint64_t val;
	memcpy((void *)&val, (void *)((char *)buf + base_offs + f->bitoffs / 8),
		sizeof(uint64_t));
	return ntohll(val);
}
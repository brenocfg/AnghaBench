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
 int /*<<< orphan*/  htonll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 

__attribute__((used)) static void _set_field64(void *buf, int base_offs, const ib_field_t * f,
			 uint64_t val)
{
	uint64_t nval;

	nval = htonll(val);
	memcpy(((void *)(char *)buf + base_offs + f->bitoffs / 8),
		(void *)&nval, sizeof(uint64_t));
}
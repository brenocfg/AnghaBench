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
struct TYPE_3__ {int /*<<< orphan*/  bitlen; int /*<<< orphan*/  (* def_dump_fn ) (char*,int,void*,int) ;} ;
typedef  TYPE_1__ ib_field_t ;

/* Variables and functions */
 int ALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (char*,int,void*,int) ; 

__attribute__((used)) static char *_mad_dump_val(const ib_field_t * f, char *buf, int bufsz,
			   void *val)
{
	f->def_dump_fn(buf, bufsz, val, ALIGN(f->bitlen, 8) / 8);
	buf[bufsz - 1] = 0;

	return buf;
}
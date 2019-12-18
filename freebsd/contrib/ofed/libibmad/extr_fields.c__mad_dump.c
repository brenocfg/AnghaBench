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
typedef  int /*<<< orphan*/  ib_mad_dump_fn ;
struct TYPE_3__ {int bitlen; int /*<<< orphan*/ * def_dump_fn; } ;
typedef  TYPE_1__ ib_field_t ;

/* Variables and functions */
 char* _mad_dump_field (TYPE_1__*,char const*,char*,int,void*) ; 
 int printf (char*,char*) ; 

__attribute__((used)) static int _mad_dump(ib_mad_dump_fn * fn, const char *name, void *val,
		     int valsz)
{
	ib_field_t f;
	char buf[512];

	f.def_dump_fn = fn;
	f.bitlen = valsz * 8;

	return printf("%s\n", _mad_dump_field(&f, name, buf, sizeof buf, val));
}
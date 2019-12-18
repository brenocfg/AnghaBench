#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* name; } ;
typedef  TYPE_1__ ib_field_t ;

/* Variables and functions */
 int /*<<< orphan*/  _mad_dump_val (TYPE_1__ const*,char*,int,void*) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int snprintf (char*,int,char*,char const*,char*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static char *_mad_dump_field(const ib_field_t * f, const char *name, char *buf,
			     int bufsz, void *val)
{
	char dots[128];
	int l, n;

	if (bufsz <= 32)
		return NULL;	/* buf too small */

	if (!name)
		name = f->name;

	l = strlen(name);
	if (l < 32) {
		memset(dots, '.', 32 - l);
		dots[32 - l] = 0;
	}

	n = snprintf(buf, bufsz, "%s:%s", name, dots);
	_mad_dump_val(f, buf + n, bufsz - n, val);
	buf[bufsz - 1] = 0;

	return buf;
}
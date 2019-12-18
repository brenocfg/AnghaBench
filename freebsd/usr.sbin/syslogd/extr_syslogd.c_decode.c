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
typedef  int /*<<< orphan*/  buf ;
struct TYPE_3__ {int c_val; scalar_t__ c_name; } ;
typedef  TYPE_1__ CODE ;

/* Variables and functions */
 int atoi (char const*) ; 
 scalar_t__ isdigit (char const) ; 
 scalar_t__ isupper (char const) ; 
 int /*<<< orphan*/  strcmp (char*,scalar_t__) ; 
 char tolower (char const) ; 

__attribute__((used)) static int
decode(const char *name, const CODE *codetab)
{
	const CODE *c;
	char *p, buf[40];

	if (isdigit(*name))
		return (atoi(name));

	for (p = buf; *name && p < &buf[sizeof(buf) - 1]; p++, name++) {
		if (isupper(*name))
			*p = tolower(*name);
		else
			*p = *name;
	}
	*p = '\0';
	for (c = codetab; c->c_name; c++)
		if (!strcmp(buf, c->c_name))
			return (c->c_val);

	return (-1);
}
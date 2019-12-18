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
struct TYPE_3__ {int c_val; scalar_t__ c_name; } ;
typedef  TYPE_1__ CODE ;

/* Variables and functions */
 int atoi (char*) ; 
 scalar_t__ isdigit (char) ; 
 int /*<<< orphan*/  strcasecmp (char*,scalar_t__) ; 

__attribute__((used)) static int
decode(char *name, const CODE *codetab)
{
	const CODE *c;

	if (isdigit(*name))
		return (atoi(name));

	for (c = codetab; c->c_name; c++)
		if (!strcasecmp(name, c->c_name))
			return (c->c_val);

	return (-1);
}
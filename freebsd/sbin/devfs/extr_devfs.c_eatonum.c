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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  atonum (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 

uint16_t
eatonum(const char *s)
{
	uint16_t num;

	if (!atonum(s, &num))
		errx(1, "error converting to number: %s", s); /* XXX clarify */
	return (num);
}
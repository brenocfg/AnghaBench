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
typedef  scalar_t__ speed_t ;
struct TYPE_3__ {scalar_t__ speed; scalar_t__ string; } ;
typedef  TYPE_1__ SPEEDS ;

/* Variables and functions */
 scalar_t__ atol (char*) ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 TYPE_1__* speeds ; 
 int /*<<< orphan*/  strcasecmp (char*,scalar_t__) ; 

__attribute__((used)) static speed_t
tset_baudrate(char *rate)
{
	SPEEDS *sp;
	speed_t speed;

	/* The baudrate number can be preceded by a 'B', which is ignored. */
	if (*rate == 'B')
		++rate;

	for (sp = speeds; sp->string; ++sp)
		if (!strcasecmp(rate, sp->string))
			return (sp->speed);
	speed = atol(rate);
	if (speed == 0)
		errx(1, "unknown baud rate %s", rate);
	return speed;
}
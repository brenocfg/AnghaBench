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

/* Variables and functions */
 scalar_t__ EDOM ; 
 scalar_t__ ERANGE ; 
 int /*<<< orphan*/  WARNING (char*,char const*) ; 
 scalar_t__ errno ; 

double errcheck(double x, const char *s)
{

	if (errno == EDOM) {
		errno = 0;
		WARNING("%s argument out of domain", s);
		x = 1;
	} else if (errno == ERANGE) {
		errno = 0;
		WARNING("%s result out of range", s);
		x = 1;
	}
	return x;
}
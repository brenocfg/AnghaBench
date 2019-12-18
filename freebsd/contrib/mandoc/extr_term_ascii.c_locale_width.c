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
struct termp {int dummy; } ;

/* Variables and functions */
 int ASCII_NBRSP ; 
 int wcwidth (int) ; 

__attribute__((used)) static size_t
locale_width(const struct termp *p, int c)
{
	int		rc;

	if (c == ASCII_NBRSP)
		c = ' ';
	rc = wcwidth(c);
	if (rc < 0)
		rc = 0;
	return rc;
}
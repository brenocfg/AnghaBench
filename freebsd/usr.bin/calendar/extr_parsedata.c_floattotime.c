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
 double SECSPERDAY ; 
 int SECSPERHOUR ; 
 int SECSPERMINUTE ; 
 scalar_t__ floor (double) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int) ; 

__attribute__((used)) static char *
floattotime(double f)
{
	static char buf[100];
	int hh, mm, ss, i;

	f -= floor(f);
	i = f * SECSPERDAY;

	hh = i / SECSPERHOUR;
	i %= SECSPERHOUR;
	mm = i / SECSPERMINUTE;
	i %= SECSPERMINUTE;
	ss = i;

	sprintf(buf, "%02d:%02d:%02d", hh, mm, ss);
	return (buf);
}
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
 char* concat (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* mkstr (char*,size_t) ; 

__attribute__((used)) static char *
p1(size_t len)
{
	char *d, *s1, *s2, *s3;
	s1 = mkstr("\\(", 60);
	s2 = mkstr("(.*)", len);
	s3 = concat(s1, s2);
	free(s2);
	free(s1);
	s1 = concat(s3, ")");
	free(s3);
	d = concat("(", s1);
	free(s1);
	return d;
}
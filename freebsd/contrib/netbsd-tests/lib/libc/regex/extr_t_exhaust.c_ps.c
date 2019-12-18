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
 char* mkstr (char const*,size_t) ; 

__attribute__((used)) static char *
ps(const char *m, const char *s, size_t len)
{
	char *d, *s1, *s2, *s3;
	s1 = mkstr(m, len);
	s2 = mkstr(s, len);
	s3 = concat(s1, s2);
	free(s2);
	free(s1);
	d = concat("(.?)", s3);
	free(s3);
	return d;
}
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
 scalar_t__ malloc (int) ; 
 scalar_t__ realloc (char*,int) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static char *
mkfullname(const char *s1, const char *s2, const char *s3)
{
	static char	*buf = NULL;
	static int	bufl = 0;
	int		f;

	f = strlen(s1) + strlen(s2) + strlen(s3) + 1;
	if (f > bufl) {
		if (buf)
			buf = (char *)realloc(buf, f);
		else
			buf = (char *)malloc(f);
	}
	if (!buf) {
		bufl = 0;
		return(NULL);
	}

	bufl = f;
	strcpy(buf, s1);
	strcat(buf, s2);
	strcat(buf, s3);
	return(buf);
}
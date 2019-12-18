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
 int /*<<< orphan*/  TRACE_IN (int (*) (char*,char**,int)) ; 
 int /*<<< orphan*/  TRACE_OUT (int (*) (char*,char**,int)) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int
strbreak(char *str, char **fields, int fields_size)
{
	char	*c = str;
	int	i, num;

	TRACE_IN(strbreak);
	num = 0;
	for (i = 0;
	     ((*fields =
	     	strsep(i < fields_size ? &c : NULL, "\n\t ")) != NULL);
	     ++i)
		if ((*(*fields)) != '\0') {
			++fields;
			++num;
		}

	TRACE_OUT(strbreak);
	return (num);
}
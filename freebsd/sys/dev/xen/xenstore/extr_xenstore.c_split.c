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
typedef  int u_int ;

/* Variables and functions */
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  M_XENSTORE ; 
 int extract_strings (char*,char const**,int) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 char** malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char const**,char*,int) ; 

__attribute__((used)) static const char **
split(char *strings, u_int len, u_int *num)
{
	const char **ret;

	/* Protect against unterminated buffers. */
	if (len > 0)
		strings[len - 1] = '\0';

	/* Count the strings. */
	*num = extract_strings(strings, /*dest*/NULL, len);

	/* Transfer to one big alloc for easy freeing by the caller. */
	ret = malloc(*num * sizeof(char *) + len, M_XENSTORE, M_WAITOK);
	memcpy(&ret[*num], strings, len);
	free(strings, M_XENSTORE);

	/* Extract pointers to newly allocated array. */
	strings = (char *)&ret[*num];
	(void)extract_strings(strings, /*dest*/ret, len);

	return (ret);
}
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
struct malloc_type {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  bcopy (char const*,char*,size_t) ; 
 char* malloc (size_t,struct malloc_type*,int /*<<< orphan*/ ) ; 
 int strnlen (char const*,size_t) ; 

char *
strndup(const char *string, size_t maxlen, struct malloc_type *type)
{
	size_t len;
	char *copy;

	len = strnlen(string, maxlen) + 1;
	copy = malloc(len, type, M_WAITOK);
	bcopy(string, copy, len);
	copy[len - 1] = '\0';
	return (copy);
}
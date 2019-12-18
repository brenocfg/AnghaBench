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
struct dtoa_context {int dummy; } ;

/* Variables and functions */
 char* rv_alloc (struct dtoa_context*,int) ; 

__attribute__((used)) static char *
nrv_alloc(struct dtoa_context* C, const char *s, char **rve, int n)
{
	char *rv, *t;

	t = rv = rv_alloc(C, n);
	while((*t = *s++)) t++;
	if (rve)
		*rve = t;
	return rv;
	}
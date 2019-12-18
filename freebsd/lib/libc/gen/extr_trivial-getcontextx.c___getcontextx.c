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
typedef  int /*<<< orphan*/  ucontext_t ;

/* Variables and functions */
 int __fillcontextx (char*) ; 
 int /*<<< orphan*/  __getcontextx_size () ; 
 int errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int /*<<< orphan*/ ) ; 

ucontext_t *
__getcontextx(void)
{
	char *ctx;
	int error;

	ctx = malloc(__getcontextx_size());
	if (ctx == NULL)
		return (NULL);
	if (__fillcontextx(ctx) == -1) {
		error = errno;
		free(ctx);
		errno = error;
		return (NULL);
	}
	return ((ucontext_t *)ctx);
}
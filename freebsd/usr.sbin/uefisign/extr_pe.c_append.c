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
struct executable {int x_len; int /*<<< orphan*/ * x_buf; } ;
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static off_t
append(struct executable *x, void *ptr, size_t len, size_t aligment)
{
	off_t off;

	off = x->x_len;
	x->x_buf = realloc(x->x_buf, x->x_len + len + aligment);
	if (x->x_buf == NULL)
		err(1, "realloc");
	memcpy(x->x_buf + x->x_len, ptr, len);
	memset(x->x_buf + x->x_len + len, 0, aligment);
	x->x_len += len + aligment;

	return (off);
}
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
struct x {char* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*) ; 

int doprint(void *_x, void *arg)
{
	struct x *x = _x;
	printf("found element <%s>\n", x->buf);
	return (int)arg;
}
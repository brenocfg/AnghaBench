#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  b1 ;
struct TYPE_3__ {void* len; int /*<<< orphan*/ * bp; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  int /*<<< orphan*/  CHAR_T ;
typedef  TYPE_1__ ARGS ;

/* Variables and functions */
 int /*<<< orphan*/  L (char*) ; 
 void* SPRINTF (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ opts_set (int /*<<< orphan*/ *,TYPE_1__**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cl_resize(SCR *sp, size_t lines, size_t columns)
{
	ARGS *argv[2], a, b;
	CHAR_T b1[1024];

	a.bp = b1;
	b.bp = NULL;
	a.len = b.len = 0;
	argv[0] = &a;
	argv[1] = &b;

	a.len = SPRINTF(b1, sizeof(b1), L("lines=%lu"), (u_long)lines);
	if (opts_set(sp, argv, NULL))
		return (1);
	a.len = SPRINTF(b1, sizeof(b1), L("columns=%lu"), (u_long)columns);
	if (opts_set(sp, argv, NULL))
		return (1);
	return (0);
}
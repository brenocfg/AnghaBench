#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct git_istream {TYPE_1__* vtbl; } ;
struct TYPE_2__ {int (* close ) (struct git_istream*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct git_istream*) ; 
 int stub1 (struct git_istream*) ; 

int close_istream(struct git_istream *st)
{
	int r = st->vtbl->close(st);
	free(st);
	return r;
}
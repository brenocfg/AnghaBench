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
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* read ) (struct git_istream*,void*,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct git_istream*,void*,size_t) ; 

ssize_t read_istream(struct git_istream *st, void *buf, size_t sz)
{
	return st->vtbl->read(st, buf, sz);
}
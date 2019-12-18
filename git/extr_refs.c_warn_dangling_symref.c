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
struct warn_if_dangling_data {char const* refname; char const* msg_fmt; int /*<<< orphan*/ * refnames; int /*<<< orphan*/ * fp; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  for_each_rawref (int /*<<< orphan*/ ,struct warn_if_dangling_data*) ; 
 int /*<<< orphan*/  warn_if_dangling_symref ; 

void warn_dangling_symref(FILE *fp, const char *msg_fmt, const char *refname)
{
	struct warn_if_dangling_data data;

	data.fp = fp;
	data.refname = refname;
	data.refnames = NULL;
	data.msg_fmt = msg_fmt;
	for_each_rawref(warn_if_dangling_symref, &data);
}
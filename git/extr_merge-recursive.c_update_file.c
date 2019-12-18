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
struct merge_options {TYPE_1__* priv; } ;
struct diff_filespec {int dummy; } ;
struct TYPE_2__ {scalar_t__ call_depth; } ;

/* Variables and functions */
 int update_file_flags (struct merge_options*,struct diff_filespec const*,char const*,int,int) ; 

__attribute__((used)) static int update_file(struct merge_options *opt,
		       int clean,
		       const struct diff_filespec *contents,
		       const char *path)
{
	return update_file_flags(opt, contents, path,
				 opt->priv->call_depth || clean, !opt->priv->call_depth);
}
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
struct stream_filter {TYPE_1__* vtbl; } ;
struct TYPE_2__ {int (* filter ) (struct stream_filter*,char const*,size_t*,char*,size_t*) ;} ;

/* Variables and functions */
 int stub1 (struct stream_filter*,char const*,size_t*,char*,size_t*) ; 

int stream_filter(struct stream_filter *filter,
		  const char *input, size_t *isize_p,
		  char *output, size_t *osize_p)
{
	return filter->vtbl->filter(filter, input, isize_p, output, osize_p);
}
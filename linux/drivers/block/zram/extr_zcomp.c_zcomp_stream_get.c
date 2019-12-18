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
struct zcomp_strm {int dummy; } ;
struct zcomp {int /*<<< orphan*/  stream; } ;

/* Variables and functions */
 struct zcomp_strm** get_cpu_ptr (int /*<<< orphan*/ ) ; 

struct zcomp_strm *zcomp_stream_get(struct zcomp *comp)
{
	return *get_cpu_ptr(comp->stream);
}
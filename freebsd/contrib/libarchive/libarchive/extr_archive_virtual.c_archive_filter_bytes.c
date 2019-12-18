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
struct archive {TYPE_1__* vtable; } ;
typedef  int /*<<< orphan*/  la_int64_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* archive_filter_bytes ) (struct archive*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct archive*,int) ; 

la_int64_t
archive_filter_bytes(struct archive *a, int n)
{
	return ((a->vtable->archive_filter_bytes)(a, n));
}
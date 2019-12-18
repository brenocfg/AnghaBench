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
typedef  int /*<<< orphan*/  la_ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* archive_write_data ) (struct archive*,void const*,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct archive*,void const*,size_t) ; 

la_ssize_t
archive_write_data(struct archive *a, const void *buff, size_t s)
{
	return ((a->vtable->archive_write_data)(a, buff, s));
}
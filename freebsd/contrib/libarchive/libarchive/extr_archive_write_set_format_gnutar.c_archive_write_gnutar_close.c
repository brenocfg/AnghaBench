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
struct archive_write {int dummy; } ;

/* Variables and functions */
 int __archive_write_nulls (struct archive_write*,int) ; 

__attribute__((used)) static int
archive_write_gnutar_close(struct archive_write *a)
{
	return (__archive_write_nulls(a, 512*2));
}
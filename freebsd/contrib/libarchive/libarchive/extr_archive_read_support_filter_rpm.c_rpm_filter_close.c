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
struct rpm {int dummy; } ;
struct archive_read_filter {scalar_t__ data; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  free (struct rpm*) ; 

__attribute__((used)) static int
rpm_filter_close(struct archive_read_filter *self)
{
	struct rpm *rpm;

	rpm = (struct rpm *)self->data;
	free(rpm);

	return (ARCHIVE_OK);
}
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
struct private_data {int /*<<< orphan*/  pdata; } ;
struct archive_write_filter {scalar_t__ data; } ;

/* Variables and functions */
 int __archive_write_program_write (struct archive_write_filter*,int /*<<< orphan*/ ,void const*,size_t) ; 

__attribute__((used)) static int
archive_compressor_program_write(struct archive_write_filter *f,
    const void *buff, size_t length)
{
	struct private_data *data = (struct private_data *)f->data;

	return __archive_write_program_write(f, data->pdata, buff, length);
}
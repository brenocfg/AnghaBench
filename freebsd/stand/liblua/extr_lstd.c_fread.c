#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t offset; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 scalar_t__ read (int /*<<< orphan*/ ,void*,size_t) ; 

size_t
fread(void *ptr, size_t size, size_t count, FILE *stream)
{
	size_t r;

	if (stream == NULL)
		return 0;
	r = (size_t)read(stream->fd, ptr, size * count);
	stream->offset += r;

	return (r);
}
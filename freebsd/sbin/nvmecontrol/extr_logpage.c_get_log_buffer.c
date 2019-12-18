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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 
 void* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
get_log_buffer(uint32_t size)
{
	void	*buf;

	if ((buf = malloc(size)) == NULL)
		errx(1, "unable to malloc %u bytes", size);

	memset(buf, 0, size);
	return (buf);
}
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
struct __printf_io {int /*<<< orphan*/  uio; int /*<<< orphan*/  fp; } ;

/* Variables and functions */
 int /*<<< orphan*/  __printf_init (struct __printf_io*) ; 
 int /*<<< orphan*/  __sfvwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
__printf_flush(struct __printf_io *io)
{

	__sfvwrite(io->fp, &io->uio);
	__printf_init(io);
}
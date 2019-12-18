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
struct rerere_io {int /*<<< orphan*/  wrerror; scalar_t__ output; } ;

/* Variables and functions */
 int /*<<< orphan*/  ferr_puts (char const*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rerere_io_putstr(const char *str, struct rerere_io *io)
{
	if (io->output)
		ferr_puts(str, io->output, &io->wrerror);
}
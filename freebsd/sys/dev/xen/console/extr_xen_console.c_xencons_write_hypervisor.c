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
struct xencons_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONSOLEIO_write ; 
 int /*<<< orphan*/  HYPERVISOR_console_io (int /*<<< orphan*/ ,unsigned int,char const*) ; 

__attribute__((used)) static int
xencons_write_hypervisor(struct xencons_priv *cons, const char *buffer,
    unsigned int size)
{

	HYPERVISOR_console_io(CONSOLEIO_write, size, buffer);

	return (size);
}
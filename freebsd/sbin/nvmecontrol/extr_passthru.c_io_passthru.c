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
struct cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  passthru (struct cmd const*,int,char**) ; 

__attribute__((used)) static void
io_passthru(const struct cmd *nf, int argc, char *argv[])
{

	passthru(nf, argc, argv);
}
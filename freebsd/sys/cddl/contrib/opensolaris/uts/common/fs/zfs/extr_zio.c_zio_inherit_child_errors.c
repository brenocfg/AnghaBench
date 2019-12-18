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
struct TYPE_3__ {scalar_t__* io_child_error; scalar_t__ io_error; } ;
typedef  TYPE_1__ zio_t ;
typedef  enum zio_child { ____Placeholder_zio_child } zio_child ;

/* Variables and functions */

__attribute__((used)) static void
zio_inherit_child_errors(zio_t *zio, enum zio_child c)
{
	if (zio->io_child_error[c] != 0 && zio->io_error == 0)
		zio->io_error = zio->io_child_error[c];
}
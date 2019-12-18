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
typedef  int /*<<< orphan*/  u_int ;
struct bhnd_erom_io {int /*<<< orphan*/  (* read ) (struct bhnd_erom_io*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  bhnd_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct bhnd_erom_io*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint32_t
bhnd_erom_io_read(struct bhnd_erom_io *eio, bhnd_size_t offset, u_int width)
{
	return (eio->read(eio, offset, width));
}
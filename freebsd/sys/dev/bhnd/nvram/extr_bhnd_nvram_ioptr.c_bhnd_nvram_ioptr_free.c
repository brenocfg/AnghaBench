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
struct bhnd_nvram_io {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bhnd_nv_free (struct bhnd_nvram_io*) ; 

__attribute__((used)) static void
bhnd_nvram_ioptr_free(struct bhnd_nvram_io *io)
{	
	bhnd_nv_free(io);
}
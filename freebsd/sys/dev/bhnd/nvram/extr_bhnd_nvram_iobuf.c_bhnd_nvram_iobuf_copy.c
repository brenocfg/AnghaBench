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
 int /*<<< orphan*/  bhnd_nvram_io_getsize (struct bhnd_nvram_io*) ; 
 struct bhnd_nvram_io* bhnd_nvram_iobuf_copy_range (struct bhnd_nvram_io*,int,int /*<<< orphan*/ ) ; 

struct bhnd_nvram_io *
bhnd_nvram_iobuf_copy(struct bhnd_nvram_io *src)
{
	return (bhnd_nvram_iobuf_copy_range(src, 0x0,
	    bhnd_nvram_io_getsize(src)));
}
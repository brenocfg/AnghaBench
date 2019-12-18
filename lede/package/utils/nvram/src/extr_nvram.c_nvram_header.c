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
typedef  int /*<<< orphan*/  nvram_header_t ;
struct TYPE_3__ {size_t offset; int /*<<< orphan*/ * mmap; } ;
typedef  TYPE_1__ nvram_handle_t ;

/* Variables and functions */

nvram_header_t * nvram_header(nvram_handle_t *h)
{
	return (nvram_header_t *) &h->mmap[h->offset];
}
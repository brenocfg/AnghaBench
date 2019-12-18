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
struct bhnd_nvram_data {int dummy; } ;
struct bhnd_nvram_btxt {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  bhnd_nvram_io_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bhnd_nvram_btxt_free(struct bhnd_nvram_data *nv)
{
	struct bhnd_nvram_btxt *btxt = (struct bhnd_nvram_btxt *)nv;
	if (btxt->data != NULL)
		bhnd_nvram_io_free(btxt->data);
}
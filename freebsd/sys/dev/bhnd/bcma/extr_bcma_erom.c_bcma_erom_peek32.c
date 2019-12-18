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
struct bcma_erom {int offset; int /*<<< orphan*/  eio; } ;

/* Variables and functions */
 int BCMA_EROM_TABLE_SIZE ; 
 int EINVAL ; 
 int /*<<< orphan*/  EROM_LOG (struct bcma_erom*,char*) ; 
 int /*<<< orphan*/  bhnd_erom_io_read (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
bcma_erom_peek32(struct bcma_erom *erom, uint32_t *entry)
{
	if (erom->offset >= (BCMA_EROM_TABLE_SIZE - sizeof(uint32_t))) {
		EROM_LOG(erom, "BCMA EROM table missing terminating EOF\n");
		return (EINVAL);
	}

	*entry = bhnd_erom_io_read(erom->eio, erom->offset, 4);
	return (0);
}
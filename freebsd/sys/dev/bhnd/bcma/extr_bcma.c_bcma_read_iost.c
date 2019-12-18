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
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_DMP_IOSTATUS ; 
 int BCMA_DMP_IOST_MASK ; 
 int bhnd_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int
bcma_read_iost(device_t dev, device_t child, uint16_t *iost)
{
	uint32_t	value;
	int		error;

	if ((error = bhnd_read_config(child, BCMA_DMP_IOSTATUS, &value, 4)))
		return (error);

	/* Return only the bottom 16 bits */
	*iost = (value & BCMA_DMP_IOST_MASK);
	return (0);
}
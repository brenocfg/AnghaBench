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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIBA_CFG0_TMSTATEHIGH ; 
 int /*<<< orphan*/  SIBA_REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TMH_SISF ; 
 int bhnd_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
siba_read_iost(device_t dev, device_t child, uint16_t *iost)
{
	uint32_t	tmhigh;
	int		error;

	error = bhnd_read_config(child, SIBA_CFG0_TMSTATEHIGH, &tmhigh, 4);
	if (error)
		return (error);

	*iost = (SIBA_REG_GET(tmhigh, TMH_SISF));
	return (0);
}
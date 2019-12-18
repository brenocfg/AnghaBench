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
typedef  int /*<<< orphan*/  U16 ;
typedef  int /*<<< orphan*/  CONFIG_PAGE_LOG_0 ;

/* Variables and functions */
 int /*<<< orphan*/  MPI_CONFIG_EXTPAGETYPE_LOG ; 
 int /*<<< orphan*/ * mpt_read_extended_config_page (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static CONFIG_PAGE_LOG_0 *
mpt_get_events(int fd, U16 *IOCStatus)
{

	return (mpt_read_extended_config_page(fd, MPI_CONFIG_EXTPAGETYPE_LOG,
	    0, 0, 0, IOCStatus));
}
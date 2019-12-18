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
typedef  int /*<<< orphan*/  U8 ;
typedef  int /*<<< orphan*/  U16 ;

/* Variables and functions */
 int /*<<< orphan*/  MPI2_CONFIG_PAGETYPE_MANUFACTURING ; 
 void* mps_read_config_page (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline void *
mps_read_man_page(int fd, U8 PageNumber, U16 *IOCStatus)
{

	return (mps_read_config_page(fd, MPI2_CONFIG_PAGETYPE_MANUFACTURING,
	    PageNumber, 0, IOCStatus));
}
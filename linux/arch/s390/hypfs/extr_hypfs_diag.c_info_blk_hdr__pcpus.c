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
struct diag204_x_info_blk_hdr {int /*<<< orphan*/  phys_cpus; } ;
struct diag204_info_blk_hdr {int /*<<< orphan*/  phys_cpus; } ;
typedef  enum diag204_format { ____Placeholder_diag204_format } diag204_format ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int DIAG204_INFO_SIMPLE ; 

__attribute__((used)) static inline __u16 info_blk_hdr__pcpus(enum diag204_format type, void *hdr)
{
	if (type == DIAG204_INFO_SIMPLE)
		return ((struct diag204_info_blk_hdr *)hdr)->phys_cpus;
	else /* DIAG204_INFO_EXT */
		return ((struct diag204_x_info_blk_hdr *)hdr)->phys_cpus;
}
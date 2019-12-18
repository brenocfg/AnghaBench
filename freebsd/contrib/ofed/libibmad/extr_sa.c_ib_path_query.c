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
typedef  int /*<<< orphan*/  ibmad_gid_t ;
typedef  int /*<<< orphan*/  ib_portid_t ;

/* Variables and functions */
 int ib_path_query_via (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  ibmp ; 

int ib_path_query(ibmad_gid_t srcgid, ibmad_gid_t destgid, ib_portid_t * sm_id,
		  void *buf)
{
	return ib_path_query_via(ibmp, srcgid, destgid, sm_id, buf);
}
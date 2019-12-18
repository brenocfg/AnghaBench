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
typedef  int /*<<< orphan*/  uint64_t ;
struct nv {int dummy; } ;

/* Variables and functions */
 scalar_t__ hio_disk_list_size ; 
 scalar_t__ hio_free_list_size ; 
 scalar_t__ hio_send_list_size ; 
 int /*<<< orphan*/  nv_add_uint64 (struct nv*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
output_status_aux(struct nv *nvout)
{

	nv_add_uint64(nvout, (uint64_t)hio_free_list_size, "idle_queue_size");
	nv_add_uint64(nvout, (uint64_t)hio_disk_list_size, "local_queue_size");
	nv_add_uint64(nvout, (uint64_t)hio_send_list_size, "send_queue_size");
}
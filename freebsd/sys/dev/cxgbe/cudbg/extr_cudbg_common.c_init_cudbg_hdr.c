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
struct cudbg_init_hdr {int init_struct_size; int /*<<< orphan*/  build_ver; int /*<<< orphan*/  minor_ver; int /*<<< orphan*/  major_ver; } ;
struct cudbg_init {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CUDBG_BUILD_VERSION ; 
 int /*<<< orphan*/  CUDBG_MAJOR_VERSION ; 
 int /*<<< orphan*/  CUDBG_MINOR_VERSION ; 

__attribute__((used)) static inline void init_cudbg_hdr(struct cudbg_init_hdr *hdr)
{
	hdr->major_ver = CUDBG_MAJOR_VERSION;
	hdr->minor_ver = CUDBG_MINOR_VERSION;
	hdr->build_ver = CUDBG_BUILD_VERSION;
	hdr->init_struct_size = sizeof(struct cudbg_init);
}
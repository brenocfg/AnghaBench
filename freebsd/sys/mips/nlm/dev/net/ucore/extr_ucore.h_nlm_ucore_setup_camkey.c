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

/* Variables and functions */
 int /*<<< orphan*/  nlm_write_ucore_cam0 (unsigned int) ; 
 int /*<<< orphan*/  nlm_write_ucore_cam1 (unsigned int) ; 
 int /*<<< orphan*/  nlm_write_ucore_cam2 (unsigned int) ; 
 int /*<<< orphan*/  nlm_write_ucore_cam3 (unsigned int) ; 

__attribute__((used)) static __inline__ void
nlm_ucore_setup_camkey(unsigned int cam_key0, unsigned int cam_key1,
    unsigned int cam_key2, unsigned int cam_key3)
{
	nlm_write_ucore_cam0(cam_key0);
	nlm_write_ucore_cam1(cam_key1);
	nlm_write_ucore_cam2(cam_key2);
	nlm_write_ucore_cam3(cam_key3);
}
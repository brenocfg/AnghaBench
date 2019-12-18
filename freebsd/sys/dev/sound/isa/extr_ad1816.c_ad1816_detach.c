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
struct ad1816_info {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ad1816_release_resources (struct ad1816_info*,int /*<<< orphan*/ ) ; 
 struct ad1816_info* pcm_getdevinfo (int /*<<< orphan*/ ) ; 
 int pcm_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ad1816_detach(device_t dev)
{
	int r;
	struct ad1816_info *ad1816;

	r = pcm_unregister(dev);
	if (r)
		return r;

	ad1816 = pcm_getdevinfo(dev);
    	ad1816_release_resources(ad1816, dev);
	return 0;
}
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
struct ess_info {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ess_release_resources (struct ess_info*,int /*<<< orphan*/ ) ; 
 struct ess_info* pcm_getdevinfo (int /*<<< orphan*/ ) ; 
 int pcm_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ess_detach(device_t dev)
{
	int r;
	struct ess_info *sc;

	r = pcm_unregister(dev);
	if (r)
		return r;

	sc = pcm_getdevinfo(dev);
    	ess_release_resources(sc, dev);
	return 0;
}
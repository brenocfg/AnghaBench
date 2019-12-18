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
struct csa_info {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  csa_releaseres (struct csa_info*,int /*<<< orphan*/ ) ; 
 struct csa_info* pcm_getdevinfo (int /*<<< orphan*/ ) ; 
 int pcm_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pcmcsa_detach(device_t dev)
{
	int r;
	struct csa_info *csa;

	r = pcm_unregister(dev);
	if (r)
		return r;

	csa = pcm_getdevinfo(dev);
	csa_releaseres(csa, dev);

	return 0;
}
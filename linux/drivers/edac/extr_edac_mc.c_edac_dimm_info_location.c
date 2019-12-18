#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mem_ctl_info {int n_layers; TYPE_1__* layers; } ;
struct dimm_info {int* location; struct mem_ctl_info* mci; } ;
struct TYPE_2__ {size_t type; } ;

/* Variables and functions */
 char** edac_layer_name ; 
 int snprintf (char*,unsigned int,char*,char*,int) ; 

unsigned int edac_dimm_info_location(struct dimm_info *dimm, char *buf,
				     unsigned int len)
{
	struct mem_ctl_info *mci = dimm->mci;
	int i, n, count = 0;
	char *p = buf;

	for (i = 0; i < mci->n_layers; i++) {
		n = snprintf(p, len, "%s %d ",
			      edac_layer_name[mci->layers[i].type],
			      dimm->location[i]);
		p += n;
		len -= n;
		count += n;
		if (!len)
			break;
	}

	return count;
}
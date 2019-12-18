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
typedef  int u_long ;
struct fileusage {int fu_id; struct fileusage* fu_next; } ;

/* Variables and functions */
 int FUHASH ; 
 struct fileusage*** fuhead ; 

struct fileusage *
lookup(u_long id, int type)
{
	struct fileusage *fup;

	for (fup = fuhead[type][id & (FUHASH-1)]; fup != NULL; fup = fup->fu_next)
		if (fup->fu_id == id)
			return (fup);
	return (NULL);
}
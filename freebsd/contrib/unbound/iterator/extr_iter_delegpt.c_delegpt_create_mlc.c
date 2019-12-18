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
typedef  int /*<<< orphan*/  uint8_t ;
struct delegpt {int dp_type_mlc; int /*<<< orphan*/  name; int /*<<< orphan*/  namelen; int /*<<< orphan*/  namelabs; } ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  dname_count_size_labels (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct delegpt*) ; 
 int /*<<< orphan*/  memdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct delegpt* delegpt_create_mlc(uint8_t* name)
{
	struct delegpt* dp=(struct delegpt*)calloc(1, sizeof(*dp));
	if(!dp)
		return NULL;
	dp->dp_type_mlc = 1;
	if(name) {
		dp->namelabs = dname_count_size_labels(name, &dp->namelen);
		dp->name = memdup(name, dp->namelen);
		if(!dp->name) {
			free(dp);
			return NULL;
		}
	}
	return dp;
}
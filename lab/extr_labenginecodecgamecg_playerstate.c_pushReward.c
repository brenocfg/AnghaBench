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
typedef  int /*<<< orphan*/  sfxHandle_t ;
typedef  int /*<<< orphan*/  qhandle_t ;
struct TYPE_2__ {int rewardStack; int* rewardCount; int /*<<< orphan*/ * rewardShader; int /*<<< orphan*/ * rewardSound; } ;

/* Variables and functions */
 int MAX_REWARDSTACK ; 
 TYPE_1__ cg ; 

__attribute__((used)) static void pushReward(sfxHandle_t sfx, qhandle_t shader, int rewardCount) {
	if (cg.rewardStack < (MAX_REWARDSTACK-1)) {
		cg.rewardStack++;
		cg.rewardSound[cg.rewardStack] = sfx;
		cg.rewardShader[cg.rewardStack] = shader;
		cg.rewardCount[cg.rewardStack] = rewardCount;
	}
}
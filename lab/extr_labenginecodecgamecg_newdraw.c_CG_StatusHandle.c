#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qhandle_t ;
struct TYPE_3__ {int /*<<< orphan*/  assaultShader; int /*<<< orphan*/  escortShader; int /*<<< orphan*/  retrieveShader; int /*<<< orphan*/  campShader; int /*<<< orphan*/  followShader; int /*<<< orphan*/  patrolShader; int /*<<< orphan*/  defendShader; } ;
struct TYPE_4__ {TYPE_1__ media; } ;

/* Variables and functions */
#define  TEAMTASK_CAMP 134 
#define  TEAMTASK_DEFENSE 133 
#define  TEAMTASK_ESCORT 132 
#define  TEAMTASK_FOLLOW 131 
#define  TEAMTASK_OFFENSE 130 
#define  TEAMTASK_PATROL 129 
#define  TEAMTASK_RETRIEVE 128 
 TYPE_2__ cgs ; 

qhandle_t CG_StatusHandle(int task) {
	qhandle_t h;
	switch (task) {
		case TEAMTASK_OFFENSE :
			h = cgs.media.assaultShader;
			break;
		case TEAMTASK_DEFENSE :
			h = cgs.media.defendShader;
			break;
		case TEAMTASK_PATROL :
			h = cgs.media.patrolShader;
			break;
		case TEAMTASK_FOLLOW :
			h = cgs.media.followShader;
			break;
		case TEAMTASK_CAMP :
			h = cgs.media.campShader;
			break;
		case TEAMTASK_RETRIEVE :
			h = cgs.media.retrieveShader; 
			break;
		case TEAMTASK_ESCORT :
			h = cgs.media.escortShader; 
			break;
		default : 
			h = cgs.media.assaultShader;
			break;
	}
	return h;
}
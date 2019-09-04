#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  float vec_t ;
typedef  float* vec3_t ;
struct TYPE_8__ {int fraction; } ;
typedef  TYPE_1__ aas_trace_t ;
struct TYPE_9__ {int areanum; int facenum; int edgenum; float* start; float* end; struct TYPE_9__* next; scalar_t__ traveltime; int /*<<< orphan*/  traveltype; } ;
typedef  TYPE_2__ aas_lreachability_t ;
struct TYPE_11__ {scalar_t__ rs_startelevator; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*) ;} ;

/* Variables and functions */
 TYPE_2__* AAS_AllocReachability () ; 
 scalar_t__ AAS_AreaGrounded (int) ; 
 scalar_t__ AAS_AreaSwim (int) ; 
 int /*<<< orphan*/  AAS_BSPModelMinsMaxsOrigin (int,float*,float*,float*,float*) ; 
 int /*<<< orphan*/  AAS_FloatForBSPEpairKey (int,char*,float*) ; 
 int AAS_NextBSPEntity (int) ; 
 int AAS_PointAreaNum (float*) ; 
 scalar_t__ AAS_ReachabilityExists (int,int) ; 
 TYPE_1__ AAS_TraceClientBBox (float*,float*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AAS_TravelFlagsForTeam (int) ; 
 int /*<<< orphan*/  AAS_ValueForBSPEpairKey (int,char*,char*,int) ; 
 int /*<<< orphan*/  AAS_VectorForBSPEpairKey (int,char*,float*) ; 
 int MAX_EPAIRKEY ; 
 int /*<<< orphan*/  PRESENCE_CROUCH ; 
 int /*<<< orphan*/  PRT_ERROR ; 
 int /*<<< orphan*/  TRAVEL_ELEVATOR ; 
 int /*<<< orphan*/  VectorAdd (float*,float*,float*) ; 
 int /*<<< orphan*/  VectorCopy (float*,float*) ; 
 int /*<<< orphan*/  VectorMA (float*,double,float*,float*) ; 
 int /*<<< orphan*/  VectorNormalize (float*) ; 
 int /*<<< orphan*/  VectorScale (float*,double,float*) ; 
 int /*<<< orphan*/  VectorSubtract (float*,float*,float*) ; 
 TYPE_5__ aassettings ; 
 TYPE_2__** areareachability ; 
 int atoi (char*) ; 
 TYPE_3__ botimport ; 
 int /*<<< orphan*/  reach_elevator ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*) ; 

void AAS_Reachability_Elevator(void)
{
	int area1num, area2num, modelnum, i, j, k, l, n, p;
	float lip, height, speed;
	char model[MAX_EPAIRKEY], classname[MAX_EPAIRKEY];
	int ent;
	vec3_t mins, maxs, origin, angles = {0, 0, 0};
	vec3_t pos1, pos2, mids, platbottom, plattop;
	vec3_t bottomorg, toporg, start, end, dir;
	vec_t xvals[8], yvals[8], xvals_top[8], yvals_top[8];
	aas_lreachability_t *lreach;
	aas_trace_t trace;

#ifdef REACH_DEBUG
	Log_Write("AAS_Reachability_Elevator\r\n");
#endif //REACH_DEBUG
	for (ent = AAS_NextBSPEntity(0); ent; ent = AAS_NextBSPEntity(ent))
	{
		if (!AAS_ValueForBSPEpairKey(ent, "classname", classname, MAX_EPAIRKEY)) continue;
		if (!strcmp(classname, "func_plat"))
		{
#ifdef REACH_DEBUG
			Log_Write("found func plat\r\n");
#endif //REACH_DEBUG
			if (!AAS_ValueForBSPEpairKey(ent, "model", model, MAX_EPAIRKEY))
			{
				botimport.Print(PRT_ERROR, "func_plat without model\n");
				continue;
			} //end if
			//get the model number, and skip the leading *
			modelnum = atoi(model+1);
			if (modelnum <= 0)
			{
				botimport.Print(PRT_ERROR, "func_plat with invalid model number\n");
				continue;
			} //end if
			//get the mins, maxs and origin of the model
			//NOTE: the origin is usually (0,0,0) and the mins and maxs
			//      are the absolute mins and maxs
			AAS_BSPModelMinsMaxsOrigin(modelnum, angles, mins, maxs, origin);
			//
			AAS_VectorForBSPEpairKey(ent, "origin", origin);
			//pos1 is the top position, pos2 is the bottom
			VectorCopy(origin, pos1);
			VectorCopy(origin, pos2);
			//get the lip of the plat
			AAS_FloatForBSPEpairKey(ent, "lip", &lip);
			if (!lip) lip = 8;
			//get the movement height of the plat
			AAS_FloatForBSPEpairKey(ent, "height", &height);
			if (!height) height = (maxs[2] - mins[2]) - lip;
			//get the speed of the plat
			AAS_FloatForBSPEpairKey(ent, "speed", &speed);
			if (!speed) speed = 200;
			//get bottom position below pos1
			pos2[2] -= height;
			//
			//get a point just above the plat in the bottom position
			VectorAdd(mins, maxs, mids);
			VectorMA(pos2, 0.5, mids, platbottom);
			platbottom[2] = maxs[2] - (pos1[2] - pos2[2]) + 2;
			//get a point just above the plat in the top position
			VectorAdd(mins, maxs, mids);
			VectorMA(pos2, 0.5, mids, plattop);
			plattop[2] = maxs[2] + 2;
			//
			/*if (!area1num)
			{
				Log_Write("no grounded area near plat bottom\r\n");
				continue;
			} //end if*/
			//get the mins and maxs a little larger
			for (i = 0; i < 3; i++)
			{
				mins[i] -= 1;
				maxs[i] += 1;
			} //end for
			//
			//botimport.Print(PRT_MESSAGE, "platbottom[2] = %1.1f plattop[2] = %1.1f\n", platbottom[2], plattop[2]);
			//
			VectorAdd(mins, maxs, mids);
			VectorScale(mids, 0.5, mids);
			//
			xvals[0] = mins[0]; xvals[1] = mids[0]; xvals[2] = maxs[0]; xvals[3] = mids[0];
			yvals[0] = mids[1]; yvals[1] = maxs[1]; yvals[2] = mids[1]; yvals[3] = mins[1];
			//
			xvals[4] = mins[0]; xvals[5] = maxs[0]; xvals[6] = maxs[0]; xvals[7] = mins[0];
			yvals[4] = maxs[1]; yvals[5] = maxs[1]; yvals[6] = mins[1]; yvals[7] = mins[1];
			//find adjacent areas around the bottom of the plat
			for (i = 0; i < 9; i++)
			{
				if (i < 8) //check at the sides of the plat
				{
					bottomorg[0] = origin[0] + xvals[i];
					bottomorg[1] = origin[1] + yvals[i];
					bottomorg[2] = platbottom[2] + 16;
					//get a grounded or swim area near the plat in the bottom position
					area1num = AAS_PointAreaNum(bottomorg);
					for (k = 0; k < 16; k++)
					{
						if (area1num)
						{
							if (AAS_AreaGrounded(area1num) || AAS_AreaSwim(area1num)) break;
						} //end if
						bottomorg[2] += 4;
						area1num = AAS_PointAreaNum(bottomorg);
					} //end if
					//if in solid
					if (k >= 16)
					{
						continue;
					} //end if
				} //end if
				else //at the middle of the plat
				{
					VectorCopy(plattop, bottomorg);
					bottomorg[2] += 24;
					area1num = AAS_PointAreaNum(bottomorg);
					if (!area1num) continue;
					VectorCopy(platbottom, bottomorg);
					bottomorg[2] += 24;
				} //end else
				//look at adjacent areas around the top of the plat
				//make larger steps to outside the plat every time
				for (n = 0; n < 3; n++)
				{
					for (k = 0; k < 3; k++)
					{
						mins[k] -= 4;
						maxs[k] += 4;
					} //end for
					xvals_top[0] = mins[0]; xvals_top[1] = mids[0]; xvals_top[2] = maxs[0]; xvals_top[3] = mids[0];
					yvals_top[0] = mids[1]; yvals_top[1] = maxs[1]; yvals_top[2] = mids[1]; yvals_top[3] = mins[1];
					//
					xvals_top[4] = mins[0]; xvals_top[5] = maxs[0]; xvals_top[6] = maxs[0]; xvals_top[7] = mins[0];
					yvals_top[4] = maxs[1]; yvals_top[5] = maxs[1]; yvals_top[6] = mins[1]; yvals_top[7] = mins[1];
					//
					for (j = 0; j < 8; j++)
					{
						toporg[0] = origin[0] + xvals_top[j];
						toporg[1] = origin[1] + yvals_top[j];
						toporg[2] = plattop[2] + 16;
						//get a grounded or swim area near the plat in the top position
						area2num = AAS_PointAreaNum(toporg);
						for (l = 0; l < 16; l++)
						{
							if (area2num)
							{
								if (AAS_AreaGrounded(area2num) || AAS_AreaSwim(area2num))
								{
									VectorCopy(plattop, start);
									start[2] += 32;
									VectorCopy(toporg, end);
									end[2] += 1;
									trace = AAS_TraceClientBBox(start, end, PRESENCE_CROUCH, -1);
									if (trace.fraction >= 1) break;
								} //end if
							} //end if
							toporg[2] += 4;
							area2num = AAS_PointAreaNum(toporg);
						} //end if
						//if in solid
						if (l >= 16) continue;
						//never create a reachability in the same area
						if (area2num == area1num) continue;
						//if the area isn't grounded
						if (!AAS_AreaGrounded(area2num)) continue;
						//if there already exists reachability between the areas
						if (AAS_ReachabilityExists(area1num, area2num)) continue;
						//if the reachability start is within the elevator bounding box
						VectorSubtract(bottomorg, platbottom, dir);
						VectorNormalize(dir);
						dir[0] = bottomorg[0] + 24 * dir[0];
						dir[1] = bottomorg[1] + 24 * dir[1];
						dir[2] = bottomorg[2];
						//
						for (p = 0; p < 3; p++)
							if (dir[p] < origin[p] + mins[p] || dir[p] > origin[p] + maxs[p]) break;
						if (p >= 3) continue;
						//create a new reachability link
						lreach = AAS_AllocReachability();
						if (!lreach) continue;
						lreach->areanum = area2num;
						//the facenum is the model number
						lreach->facenum = modelnum;
						//the edgenum is the height
						lreach->edgenum = (int) height;
						//
						VectorCopy(dir, lreach->start);
						VectorCopy(toporg, lreach->end);
						lreach->traveltype = TRAVEL_ELEVATOR;
						lreach->traveltype |= AAS_TravelFlagsForTeam(ent);
						lreach->traveltime = aassettings.rs_startelevator + height * 100 / speed;
						lreach->next = areareachability[area1num];
						areareachability[area1num] = lreach;
						//don't go any further to the outside
						n = 9999;
						//
#ifdef REACH_DEBUG
						Log_Write("elevator reach from %d to %d\r\n", area1num, area2num);
#endif //REACH_DEBUG
						//
						reach_elevator++;
					} //end for
				} //end for
			} //end for
		} //end if
	} //end for
}
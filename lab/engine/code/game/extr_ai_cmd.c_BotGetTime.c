#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int subtype; scalar_t__ type; } ;
typedef  TYPE_1__ bot_match_t ;

/* Variables and functions */
 float FloatTime () ; 
 int MAX_MESSAGE_SIZE ; 
 scalar_t__ MSG_FORALONGTIME ; 
 scalar_t__ MSG_FORAWHILE ; 
 scalar_t__ MSG_FOREVER ; 
 scalar_t__ MSG_MINUTES ; 
 scalar_t__ MSG_SECONDS ; 
 int /*<<< orphan*/  MTCONTEXT_TIME ; 
 int ST_TIME ; 
 int /*<<< orphan*/  TIME ; 
 int atof (char*) ; 
 scalar_t__ trap_BotFindMatch (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_BotMatchVariable (TYPE_1__*,int /*<<< orphan*/ ,char*,int) ; 

float BotGetTime(bot_match_t *match) {
	bot_match_t timematch;
	char timestring[MAX_MESSAGE_SIZE];
	float t;

	//if the matched string has a time
	if (match->subtype & ST_TIME) {
		//get the time string
		trap_BotMatchVariable(match, TIME, timestring, MAX_MESSAGE_SIZE);
		//match it to find out if the time is in seconds or minutes
		if (trap_BotFindMatch(timestring, &timematch, MTCONTEXT_TIME)) {
			if (timematch.type == MSG_FOREVER) {
				t = 99999999.0f;
			}
			else if (timematch.type == MSG_FORAWHILE) {
				t = 10 * 60; // 10 minutes
			}
			else if (timematch.type == MSG_FORALONGTIME) {
				t = 30 * 60; // 30 minutes
			}
			else {
				trap_BotMatchVariable(&timematch, TIME, timestring, MAX_MESSAGE_SIZE);
				if (timematch.type == MSG_MINUTES) t = atof(timestring) * 60;
				else if (timematch.type == MSG_SECONDS) t = atof(timestring);
				else t = 0;
			}
			//if there's a valid time
			if (t > 0) return FloatTime() + t;
		}
	}
	return 0;
}
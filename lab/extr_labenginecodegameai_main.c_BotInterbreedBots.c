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
struct TYPE_2__ {int num_kills; int num_deaths; scalar_t__ inuse; int /*<<< orphan*/  gs; } ;

/* Variables and functions */
 int MAX_CLIENTS ; 
 TYPE_1__** botstates ; 
 int /*<<< orphan*/  trap_BotInterbreedGoalFuzzyLogic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_BotMutateGoalFuzzyLogic (int /*<<< orphan*/ ,int) ; 
 scalar_t__ trap_GeneticParentsAndChildSelection (int,float*,int*,int*,int*) ; 

void BotInterbreedBots(void) {
	float ranks[MAX_CLIENTS];
	int parent1, parent2, child;
	int i;

	// get rankings for all the bots
	for (i = 0; i < MAX_CLIENTS; i++) {
		if ( botstates[i] && botstates[i]->inuse ) {
			ranks[i] = botstates[i]->num_kills * 2 - botstates[i]->num_deaths;
		}
		else {
			ranks[i] = -1;
		}
	}

	if (trap_GeneticParentsAndChildSelection(MAX_CLIENTS, ranks, &parent1, &parent2, &child)) {
		trap_BotInterbreedGoalFuzzyLogic(botstates[parent1]->gs, botstates[parent2]->gs, botstates[child]->gs);
		trap_BotMutateGoalFuzzyLogic(botstates[child]->gs, 1);
	}
	// reset the kills and deaths
	for (i = 0; i < MAX_CLIENTS; i++) {
		if (botstates[i] && botstates[i]->inuse) {
			botstates[i]->num_kills = 0;
			botstates[i]->num_deaths = 0;
		}
	}
}
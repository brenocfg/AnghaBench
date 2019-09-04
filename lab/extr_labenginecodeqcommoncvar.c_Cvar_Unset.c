#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {size_t hashIndex; TYPE_2__* hashPrev; TYPE_4__* hashNext; TYPE_1__* prev; struct TYPE_11__* next; scalar_t__ description; scalar_t__ resetString; scalar_t__ latchedString; scalar_t__ string; scalar_t__ name; int /*<<< orphan*/  flags; } ;
typedef  TYPE_3__ cvar_t ;
struct TYPE_12__ {TYPE_2__* hashPrev; } ;
struct TYPE_10__ {TYPE_4__* hashNext; } ;
struct TYPE_9__ {TYPE_3__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Memset (TYPE_3__*,char,int) ; 
 int /*<<< orphan*/  Z_Free (scalar_t__) ; 
 int /*<<< orphan*/  cvar_modifiedFlags ; 
 TYPE_3__* cvar_vars ; 
 TYPE_4__** hashTable ; 

cvar_t *Cvar_Unset(cvar_t *cv)
{
	cvar_t *next = cv->next;

	// note what types of cvars have been modified (userinfo, archive, serverinfo, systeminfo)
	cvar_modifiedFlags |= cv->flags;

	if(cv->name)
		Z_Free(cv->name);
	if(cv->string)
		Z_Free(cv->string);
	if(cv->latchedString)
		Z_Free(cv->latchedString);
	if(cv->resetString)
		Z_Free(cv->resetString);
	if(cv->description)
		Z_Free(cv->description);

	if(cv->prev)
		cv->prev->next = cv->next;
	else
		cvar_vars = cv->next;
	if(cv->next)
		cv->next->prev = cv->prev;

	if(cv->hashPrev)
		cv->hashPrev->hashNext = cv->hashNext;
	else
		hashTable[cv->hashIndex] = cv->hashNext;
	if(cv->hashNext)
		cv->hashNext->hashPrev = cv->hashPrev;

	Com_Memset(cv, '\0', sizeof(*cv));
	
	return next;
}
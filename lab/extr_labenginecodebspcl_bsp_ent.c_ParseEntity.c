#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  string; } ;
typedef  TYPE_1__ token_t ;
typedef  int /*<<< orphan*/  script_t ;
typedef  int qboolean ;
struct TYPE_8__ {struct TYPE_8__* next; } ;
typedef  TYPE_2__ epair_t ;
struct TYPE_9__ {TYPE_2__* epairs; } ;
typedef  TYPE_3__ entity_t ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 size_t MAX_MAP_ENTITIES ; 
 int /*<<< orphan*/  PS_ReadToken (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  PS_UnreadLastToken (int /*<<< orphan*/ *) ; 
 TYPE_2__* ParseEpair (int /*<<< orphan*/ *) ; 
 TYPE_3__* entities ; 
 size_t num_entities ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

qboolean	ParseEntity(script_t *script)
{
	epair_t *e;
	entity_t	*mapent;
	token_t token;

	if (!PS_ReadToken(script, &token))
		return false;

	if (strcmp(token.string, "{"))
		Error ("ParseEntity: { not found");
	
	if (num_entities == MAX_MAP_ENTITIES)
		Error ("num_entities == MAX_MAP_ENTITIES");

	mapent = &entities[num_entities];
	num_entities++;

	do
	{
		if (!PS_ReadToken(script, &token))
			Error ("ParseEntity: EOF without closing brace");
		if (!strcmp(token.string, "}") )
			break;
		PS_UnreadLastToken(script);
		e = ParseEpair(script);
		e->next = mapent->epairs;
		mapent->epairs = e;
	} while (1);
	
	return true;
}
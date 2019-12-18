#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ type; int /*<<< orphan*/  string; } ;
typedef  TYPE_1__ token_t ;
typedef  int /*<<< orphan*/  script_t ;
struct TYPE_9__ {char* key; char* value; struct TYPE_9__* next; } ;
typedef  TYPE_2__ bsp_epair_t ;
struct TYPE_10__ {TYPE_2__* epairs; } ;
typedef  TYPE_3__ bsp_entity_t ;
struct TYPE_12__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*) ;} ;
struct TYPE_11__ {int numentities; TYPE_3__* entities; int /*<<< orphan*/  entdatasize; int /*<<< orphan*/  dentdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_FreeBSPEntities () ; 
 int /*<<< orphan*/  FreeScript (int /*<<< orphan*/ *) ; 
 scalar_t__ GetClearedHunkMemory (int) ; 
 scalar_t__ GetHunkMemory (scalar_t__) ; 
 int /*<<< orphan*/ * LoadScriptMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int MAX_BSPENTITIES ; 
 int /*<<< orphan*/  PRT_MESSAGE ; 
 int /*<<< orphan*/  PS_ExpectTokenType (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ PS_ReadToken (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int SCFL_NOSTRINGESCAPECHARS ; 
 int SCFL_NOSTRINGWHITESPACES ; 
 int /*<<< orphan*/  ScriptError (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  SetScriptFlags (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  StripDoubleQuotes (int /*<<< orphan*/ ) ; 
 scalar_t__ TT_STRING ; 
 TYPE_5__ botimport ; 
 TYPE_4__ bspworld ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 

void AAS_ParseBSPEntities(void)
{
	script_t *script;
	token_t token;
	bsp_entity_t *ent;
	bsp_epair_t *epair;

	script = LoadScriptMemory(bspworld.dentdata, bspworld.entdatasize, "entdata");
	SetScriptFlags(script, SCFL_NOSTRINGWHITESPACES|SCFL_NOSTRINGESCAPECHARS);//SCFL_PRIMITIVE);

	bspworld.numentities = 1;

	while(PS_ReadToken(script, &token))
	{
		if (strcmp(token.string, "{"))
		{
			ScriptError(script, "invalid %s", token.string);
			AAS_FreeBSPEntities();
			FreeScript(script);
			return;
		} //end if
		if (bspworld.numentities >= MAX_BSPENTITIES)
		{
			botimport.Print(PRT_MESSAGE, "too many entities in BSP file\n");
			break;
		} //end if
		ent = &bspworld.entities[bspworld.numentities];
		bspworld.numentities++;
		ent->epairs = NULL;
		while(PS_ReadToken(script, &token))
		{
			if (!strcmp(token.string, "}")) break;
			epair = (bsp_epair_t *) GetClearedHunkMemory(sizeof(bsp_epair_t));
			epair->next = ent->epairs;
			ent->epairs = epair;
			if (token.type != TT_STRING)
			{
				ScriptError(script, "invalid %s", token.string);
				AAS_FreeBSPEntities();
				FreeScript(script);
				return;
			} //end if
			StripDoubleQuotes(token.string);
			epair->key = (char *) GetHunkMemory(strlen(token.string) + 1);
			strcpy(epair->key, token.string);
			if (!PS_ExpectTokenType(script, TT_STRING, 0, &token))
			{
				AAS_FreeBSPEntities();
				FreeScript(script);
				return;
			} //end if
			StripDoubleQuotes(token.string);
			epair->value = (char *) GetHunkMemory(strlen(token.string) + 1);
			strcpy(epair->value, token.string);
		} //end while
		if (strcmp(token.string, "}"))
		{
			ScriptError(script, "missing }");
			AAS_FreeBSPEntities();
			FreeScript(script);
			return;
		} //end if
	} //end while
	FreeScript(script);
}
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
typedef  int /*<<< orphan*/  strippedName ;
struct TYPE_7__ {int /*<<< orphan*/  timeOffset; struct TYPE_7__* remappedShader; int /*<<< orphan*/  name; struct TYPE_7__* next; } ;
typedef  TYPE_1__ shader_t ;
typedef  int /*<<< orphan*/  qhandle_t ;
struct TYPE_9__ {int /*<<< orphan*/  (* Printf ) (int /*<<< orphan*/ ,char*,char const*) ;} ;
struct TYPE_8__ {TYPE_1__* defaultShader; } ;

/* Variables and functions */
 int /*<<< orphan*/  COM_StripExtension (char const*,char*,int) ; 
 int /*<<< orphan*/  FILE_HASH_SIZE ; 
 int MAX_QPATH ; 
 int /*<<< orphan*/  PRINT_WARNING ; 
 scalar_t__ Q_stricmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RE_RegisterShaderLightMap (char const*,int /*<<< orphan*/ ) ; 
 TYPE_1__* R_FindShaderByName (char const*) ; 
 TYPE_1__* R_GetShaderByHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atof (char const*) ; 
 int generateHashValue (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__** hashTable ; 
 TYPE_3__ ri ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*,char const*) ; 
 TYPE_2__ tr ; 

void R_RemapShader(const char *shaderName, const char *newShaderName, const char *timeOffset) {
	char		strippedName[MAX_QPATH];
	int			hash;
	shader_t	*sh, *sh2;
	qhandle_t	h;

	sh = R_FindShaderByName( shaderName );
	if (sh == NULL || sh == tr.defaultShader) {
		h = RE_RegisterShaderLightMap(shaderName, 0);
		sh = R_GetShaderByHandle(h);
	}
	if (sh == NULL || sh == tr.defaultShader) {
		ri.Printf( PRINT_WARNING, "WARNING: R_RemapShader: shader %s not found\n", shaderName );
		return;
	}

	sh2 = R_FindShaderByName( newShaderName );
	if (sh2 == NULL || sh2 == tr.defaultShader) {
		h = RE_RegisterShaderLightMap(newShaderName, 0);
		sh2 = R_GetShaderByHandle(h);
	}

	if (sh2 == NULL || sh2 == tr.defaultShader) {
		ri.Printf( PRINT_WARNING, "WARNING: R_RemapShader: new shader %s not found\n", newShaderName );
		return;
	}

	// remap all the shaders with the given name
	// even tho they might have different lightmaps
	COM_StripExtension(shaderName, strippedName, sizeof(strippedName));
	hash = generateHashValue(strippedName, FILE_HASH_SIZE);
	for (sh = hashTable[hash]; sh; sh = sh->next) {
		if (Q_stricmp(sh->name, strippedName) == 0) {
			if (sh != sh2) {
				sh->remappedShader = sh2;
			} else {
				sh->remappedShader = NULL;
			}
		}
	}
	if (timeOffset) {
		sh2->timeOffset = atof(timeOffset);
	}
}
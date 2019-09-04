#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  index; scalar_t__ defaultShader; } ;
typedef  TYPE_1__ shader_t ;
typedef  int /*<<< orphan*/  qhandle_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* Printf ) (int /*<<< orphan*/ ,char*) ;} ;

/* Variables and functions */
 scalar_t__ MAX_QPATH ; 
 int /*<<< orphan*/  PRINT_ALL ; 
 TYPE_1__* R_FindShader (char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_2__ ri ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 

qhandle_t RE_RegisterShaderLightMap( const char *name, int lightmapIndex ) {
	shader_t	*sh;

	if ( strlen( name ) >= MAX_QPATH ) {
		ri.Printf( PRINT_ALL, "Shader name exceeds MAX_QPATH\n" );
		return 0;
	}

	sh = R_FindShader( name, lightmapIndex, qtrue );

	// we want to return 0 if the shader failed to
	// load for some reason, but R_FindShader should
	// still keep a name allocated for it, so if
	// something calls RE_RegisterShader again with
	// the same name, we don't try looking for it again
	if ( sh->defaultShader ) {
		return 0;
	}

	return sh->index;
}
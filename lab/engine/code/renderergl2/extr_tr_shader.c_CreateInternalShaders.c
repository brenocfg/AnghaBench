#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  sort; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/  stateBits; int /*<<< orphan*/  active; TYPE_1__* bundle; } ;
struct TYPE_6__ {void* shadowShader; void* defaultShader; int /*<<< orphan*/  defaultImage; scalar_t__ numShaders; } ;
struct TYPE_5__ {int /*<<< orphan*/ * image; } ;

/* Variables and functions */
 void* FinishShader () ; 
 int /*<<< orphan*/  GLS_DEFAULT ; 
 int /*<<< orphan*/  InitShader (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIGHTMAP_NONE ; 
 int /*<<< orphan*/  Q_strncpyz (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  SS_STENCIL_SHADOW ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_4__ shader ; 
 TYPE_3__* stages ; 
 TYPE_2__ tr ; 

__attribute__((used)) static void CreateInternalShaders( void ) {
	tr.numShaders = 0;

	// init the default shader
	InitShader( "<default>", LIGHTMAP_NONE );
	stages[0].bundle[0].image[0] = tr.defaultImage;
	stages[0].active = qtrue;
	stages[0].stateBits = GLS_DEFAULT;
	tr.defaultShader = FinishShader();

	// shadow shader is just a marker
	Q_strncpyz( shader.name, "<stencil shadow>", sizeof( shader.name ) );
	shader.sort = SS_STENCIL_SHADOW;
	tr.shadowShader = FinishShader();
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ glslShaderGroup; int glslShaderIndex; int rgbGen; int alphaGen; TYPE_1__* bundle; int /*<<< orphan*/  active; } ;
typedef  TYPE_2__ shaderStage_t ;
struct TYPE_11__ {int deformation; } ;
typedef  TYPE_3__ deformStage_t ;
struct TYPE_15__ {scalar_t__ integer; } ;
struct TYPE_14__ {scalar_t__ integer; } ;
struct TYPE_13__ {int vertexAttribs; int numDeforms; TYPE_3__* deforms; scalar_t__ defaultShader; scalar_t__ isPortal; } ;
struct TYPE_12__ {scalar_t__ lightallShader; } ;
struct TYPE_9__ {scalar_t__* image; int tcGen; } ;

/* Variables and functions */
#define  AGEN_LIGHTING_SPECULAR 157 
#define  AGEN_ONE_MINUS_VERTEX 156 
#define  AGEN_VERTEX 155 
 int ATTR_COLOR ; 
 int ATTR_LIGHTCOORD ; 
 int ATTR_LIGHTDIRECTION ; 
 int ATTR_NORMAL ; 
 int ATTR_POSITION ; 
 int ATTR_TANGENT ; 
 int ATTR_TEXCOORD ; 
#define  CGEN_EXACT_VERTEX 154 
#define  CGEN_EXACT_VERTEX_LIT 153 
#define  CGEN_LIGHTING_DIFFUSE 152 
#define  CGEN_ONE_MINUS_VERTEX 151 
#define  CGEN_VERTEX 150 
#define  CGEN_VERTEX_LIT 149 
#define  DEFORM_AUTOSPRITE 148 
#define  DEFORM_AUTOSPRITE2 147 
#define  DEFORM_BULGE 146 
#define  DEFORM_MOVE 145 
#define  DEFORM_NONE 144 
#define  DEFORM_NORMALS 143 
#define  DEFORM_PROJECTION_SHADOW 142 
#define  DEFORM_TEXT0 141 
#define  DEFORM_TEXT1 140 
#define  DEFORM_TEXT2 139 
#define  DEFORM_TEXT3 138 
#define  DEFORM_TEXT4 137 
#define  DEFORM_TEXT5 136 
#define  DEFORM_TEXT6 135 
#define  DEFORM_TEXT7 134 
#define  DEFORM_WAVE 133 
 int LIGHTDEF_LIGHTTYPE_MASK ; 
#define  LIGHTDEF_USE_LIGHTMAP 132 
#define  LIGHTDEF_USE_LIGHT_VERTEX 131 
 int MAX_SHADER_STAGES ; 
 int NUM_TEXTURE_BUNDLES ; 
#define  TCGEN_ENVIRONMENT_MAPPED 130 
#define  TCGEN_LIGHTMAP 129 
#define  TCGEN_TEXTURE 128 
 TYPE_8__* r_normalMapping ; 
 TYPE_7__* r_specularMapping ; 
 TYPE_6__ shader ; 
 TYPE_2__* stages ; 
 TYPE_4__ tr ; 

__attribute__((used)) static void ComputeVertexAttribs(void)
{
	int i, stage;

	// dlights always need ATTR_NORMAL
	shader.vertexAttribs = ATTR_POSITION | ATTR_NORMAL;

	// portals always need normals, for SurfIsOffscreen()
	if (shader.isPortal)
	{
		shader.vertexAttribs |= ATTR_NORMAL;
	}

	if (shader.defaultShader)
	{
		shader.vertexAttribs |= ATTR_TEXCOORD;
		return;
	}

	if(shader.numDeforms)
	{
		for ( i = 0; i < shader.numDeforms; i++)
		{
			deformStage_t  *ds = &shader.deforms[i];

			switch (ds->deformation)
			{
				case DEFORM_BULGE:
					shader.vertexAttribs |= ATTR_NORMAL | ATTR_TEXCOORD;
					break;

				case DEFORM_AUTOSPRITE:
					shader.vertexAttribs |= ATTR_NORMAL | ATTR_COLOR;
					break;

				case DEFORM_WAVE:
				case DEFORM_NORMALS:
				case DEFORM_TEXT0:
				case DEFORM_TEXT1:
				case DEFORM_TEXT2:
				case DEFORM_TEXT3:
				case DEFORM_TEXT4:
				case DEFORM_TEXT5:
				case DEFORM_TEXT6:
				case DEFORM_TEXT7:
					shader.vertexAttribs |= ATTR_NORMAL;
					break;

				default:
				case DEFORM_NONE:
				case DEFORM_MOVE:
				case DEFORM_PROJECTION_SHADOW:
				case DEFORM_AUTOSPRITE2:
					break;
			}
		}
	}

	for ( stage = 0; stage < MAX_SHADER_STAGES; stage++ )
	{
		shaderStage_t *pStage = &stages[stage];

		if ( !pStage->active ) 
		{
			break;
		}

		if (pStage->glslShaderGroup == tr.lightallShader)
		{
			shader.vertexAttribs |= ATTR_NORMAL;

			if ((pStage->glslShaderIndex & LIGHTDEF_LIGHTTYPE_MASK) && !(r_normalMapping->integer == 0 && r_specularMapping->integer == 0))
			{
				shader.vertexAttribs |= ATTR_TANGENT;
			}

			switch (pStage->glslShaderIndex & LIGHTDEF_LIGHTTYPE_MASK)
			{
				case LIGHTDEF_USE_LIGHTMAP:
				case LIGHTDEF_USE_LIGHT_VERTEX:
					shader.vertexAttribs |= ATTR_LIGHTDIRECTION;
					break;
				default:
					break;
			}
		}

		for (i = 0; i < NUM_TEXTURE_BUNDLES; i++)
		{
			if ( pStage->bundle[i].image[0] == 0 )
			{
				continue;
			}

			switch(pStage->bundle[i].tcGen)
			{
				case TCGEN_TEXTURE:
					shader.vertexAttribs |= ATTR_TEXCOORD;
					break;
				case TCGEN_LIGHTMAP:
					shader.vertexAttribs |= ATTR_LIGHTCOORD;
					break;
				case TCGEN_ENVIRONMENT_MAPPED:
					shader.vertexAttribs |= ATTR_NORMAL;
					break;

				default:
					break;
			}
		}

		switch(pStage->rgbGen)
		{
			case CGEN_EXACT_VERTEX:
			case CGEN_VERTEX:
			case CGEN_EXACT_VERTEX_LIT:
			case CGEN_VERTEX_LIT:
			case CGEN_ONE_MINUS_VERTEX:
				shader.vertexAttribs |= ATTR_COLOR;
				break;

			case CGEN_LIGHTING_DIFFUSE:
				shader.vertexAttribs |= ATTR_NORMAL;
				break;

			default:
				break;
		}

		switch(pStage->alphaGen)
		{
			case AGEN_LIGHTING_SPECULAR:
				shader.vertexAttribs |= ATTR_NORMAL;
				break;

			case AGEN_VERTEX:
			case AGEN_ONE_MINUS_VERTEX:
				shader.vertexAttribs |= ATTR_COLOR;
				break;

			default:
				break;
		}
	}
}
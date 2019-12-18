#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ vidHeight; scalar_t__ vidWidth; } ;
struct TYPE_9__ {int glslMajorVersion; int glslMinorVersion; } ;
struct TYPE_8__ {scalar_t__ integer; } ;
struct TYPE_7__ {int integer; } ;
struct TYPE_6__ {scalar_t__ integer; } ;
typedef  scalar_t__ GLenum ;
typedef  char GLchar ;

/* Variables and functions */
 int /*<<< orphan*/  AGEN_LIGHTING_SPECULAR ; 
 int /*<<< orphan*/  AGEN_PORTAL ; 
 int CGEN_LIGHTING_DIFFUSE ; 
 int /*<<< orphan*/  DGEN_BULGE ; 
 int /*<<< orphan*/  DGEN_MOVE ; 
 int /*<<< orphan*/  DGEN_WAVE_INVERSE_SAWTOOTH ; 
 int /*<<< orphan*/  DGEN_WAVE_SAWTOOTH ; 
 int /*<<< orphan*/  DGEN_WAVE_SIN ; 
 int /*<<< orphan*/  DGEN_WAVE_SQUARE ; 
 int /*<<< orphan*/  DGEN_WAVE_TRIANGLE ; 
 scalar_t__ GL_VERTEX_SHADER ; 
 int MAX (int,int) ; 
 int /*<<< orphan*/  Q_strcat (char*,int,char const*) ; 
 int /*<<< orphan*/  TCGEN_ENVIRONMENT_MAPPED ; 
 int /*<<< orphan*/  TCGEN_FOG ; 
 int /*<<< orphan*/  TCGEN_LIGHTMAP ; 
 int /*<<< orphan*/  TCGEN_TEXTURE ; 
 int /*<<< orphan*/  TCGEN_VECTOR ; 
 TYPE_5__ glConfig ; 
 TYPE_4__ glRefConfig ; 
 TYPE_3__* r_cubeMapping ; 
 TYPE_2__* r_cubemapSize ; 
 TYPE_1__* r_pbr ; 
 char* va (char*,int,...) ; 

__attribute__((used)) static void GLSL_GetShaderHeader( GLenum shaderType, const GLchar *extra, char *dest, int size )
{
	float fbufWidthScale, fbufHeightScale;

	dest[0] = '\0';

	// HACK: abuse the GLSL preprocessor to turn GLSL 1.20 shaders into 1.30 ones
	if(glRefConfig.glslMajorVersion > 1 || (glRefConfig.glslMajorVersion == 1 && glRefConfig.glslMinorVersion >= 30))
	{
		if (glRefConfig.glslMajorVersion > 1 || (glRefConfig.glslMajorVersion == 1 && glRefConfig.glslMinorVersion >= 50))
			Q_strcat(dest, size, "#version 150\n");
		else
			Q_strcat(dest, size, "#version 130\n");

		if(shaderType == GL_VERTEX_SHADER)
		{
			Q_strcat(dest, size, "#define attribute in\n");
			Q_strcat(dest, size, "#define varying out\n");
		}
		else
		{
			Q_strcat(dest, size, "#define varying in\n");

			Q_strcat(dest, size, "out vec4 out_Color;\n");
			Q_strcat(dest, size, "#define gl_FragColor out_Color\n");
			Q_strcat(dest, size, "#define texture2D texture\n");
			Q_strcat(dest, size, "#define textureCubeLod textureLod\n");
			Q_strcat(dest, size, "#define shadow2D texture\n");
		}
	}
	else
	{
		Q_strcat(dest, size, "#version 120\n");
		Q_strcat(dest, size, "#define shadow2D(a,b) shadow2D(a,b).r \n");
	}

	// HACK: add some macros to avoid extra uniforms and save speed and code maintenance
	//Q_strcat(dest, size,
	//		 va("#ifndef r_SpecularExponent\n#define r_SpecularExponent %f\n#endif\n", r_specularExponent->value));
	//Q_strcat(dest, size,
	//		 va("#ifndef r_SpecularScale\n#define r_SpecularScale %f\n#endif\n", r_specularScale->value));
	//Q_strcat(dest, size,
	//       va("#ifndef r_NormalScale\n#define r_NormalScale %f\n#endif\n", r_normalScale->value));


	Q_strcat(dest, size, "#ifndef M_PI\n#define M_PI 3.14159265358979323846\n#endif\n");

	//Q_strcat(dest, size, va("#ifndef MAX_SHADOWMAPS\n#define MAX_SHADOWMAPS %i\n#endif\n", MAX_SHADOWMAPS));

	Q_strcat(dest, size,
					 va("#ifndef deformGen_t\n"
						"#define deformGen_t\n"
						"#define DGEN_WAVE_SIN %i\n"
						"#define DGEN_WAVE_SQUARE %i\n"
						"#define DGEN_WAVE_TRIANGLE %i\n"
						"#define DGEN_WAVE_SAWTOOTH %i\n"
						"#define DGEN_WAVE_INVERSE_SAWTOOTH %i\n"
						"#define DGEN_BULGE %i\n"
						"#define DGEN_MOVE %i\n"
						"#endif\n",
						DGEN_WAVE_SIN,
						DGEN_WAVE_SQUARE,
						DGEN_WAVE_TRIANGLE,
						DGEN_WAVE_SAWTOOTH,
						DGEN_WAVE_INVERSE_SAWTOOTH,
						DGEN_BULGE,
						DGEN_MOVE));

	Q_strcat(dest, size,
					 va("#ifndef tcGen_t\n"
						"#define tcGen_t\n"
						"#define TCGEN_LIGHTMAP %i\n"
						"#define TCGEN_TEXTURE %i\n"
						"#define TCGEN_ENVIRONMENT_MAPPED %i\n"
						"#define TCGEN_FOG %i\n"
						"#define TCGEN_VECTOR %i\n"
						"#endif\n",
						TCGEN_LIGHTMAP,
						TCGEN_TEXTURE,
						TCGEN_ENVIRONMENT_MAPPED,
						TCGEN_FOG,
						TCGEN_VECTOR));

	Q_strcat(dest, size,
					 va("#ifndef colorGen_t\n"
						"#define colorGen_t\n"
						"#define CGEN_LIGHTING_DIFFUSE %i\n"
						"#endif\n",
						CGEN_LIGHTING_DIFFUSE));

	Q_strcat(dest, size,
							 va("#ifndef alphaGen_t\n"
								"#define alphaGen_t\n"
								"#define AGEN_LIGHTING_SPECULAR %i\n"
								"#define AGEN_PORTAL %i\n"
								"#endif\n",
								AGEN_LIGHTING_SPECULAR,
								AGEN_PORTAL));

	fbufWidthScale = 1.0f / ((float)glConfig.vidWidth);
	fbufHeightScale = 1.0f / ((float)glConfig.vidHeight);
	Q_strcat(dest, size,
			 va("#ifndef r_FBufScale\n#define r_FBufScale vec2(%f, %f)\n#endif\n", fbufWidthScale, fbufHeightScale));

	if (r_pbr->integer)
		Q_strcat(dest, size, "#define USE_PBR\n");

	if (r_cubeMapping->integer)
	{
		int cubeMipSize = r_cubemapSize->integer;
		int numRoughnessMips = 0;

		while (cubeMipSize)
		{
			cubeMipSize >>= 1;
			numRoughnessMips++;
		}
		numRoughnessMips = MAX(1, numRoughnessMips - 2);
		Q_strcat(dest, size, va("#define ROUGHNESS_MIPS float(%d)\n", numRoughnessMips));
	}

	if (extra)
	{
		Q_strcat(dest, size, extra);
	}

	// OK we added a lot of stuff but if we do something bad in the GLSL shaders then we want the proper line
	// so we have to reset the line counting
	Q_strcat(dest, size, "#line 0\n");
}
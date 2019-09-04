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
struct TYPE_2__ {int /*<<< orphan*/  (* Cmd_AddCommand ) (char*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* Cvar_Get ) (char*,char*,int) ;int /*<<< orphan*/  (* Cvar_CheckRange ) (int /*<<< orphan*/ ,float,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int CVAR_ARCHIVE ; 
 int CVAR_CHEAT ; 
 int CVAR_LATCH ; 
 int CVAR_TEMP ; 
 char* FLARE_STDCOEFF ; 
 int /*<<< orphan*/  GLimp_Minimize ; 
 int /*<<< orphan*/  GfxInfo_f ; 
 int /*<<< orphan*/  GfxMemInfo_f ; 
 int /*<<< orphan*/  MAX_POLYS ; 
 int /*<<< orphan*/  MAX_POLYVERTS ; 
 int /*<<< orphan*/  R_ExportCubemaps_f ; 
 int /*<<< orphan*/  R_ImageList_f ; 
 int /*<<< orphan*/  R_ModeList_f ; 
 int /*<<< orphan*/  R_Modellist_f ; 
 int /*<<< orphan*/  R_ScreenShotJPEG_f ; 
 int /*<<< orphan*/  R_ScreenShot_f ; 
 int /*<<< orphan*/  R_ShaderList_f ; 
 int /*<<< orphan*/  R_SkinList_f ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  r_allowExtensions ; 
 int /*<<< orphan*/  r_ambientScale ; 
 int /*<<< orphan*/  r_anaglyphMode ; 
 int /*<<< orphan*/  r_arb_seamless_cube_map ; 
 int /*<<< orphan*/  r_arb_vertex_array_object ; 
 int /*<<< orphan*/  r_autoExposure ; 
 int /*<<< orphan*/  r_aviMotionJpegQuality ; 
 int /*<<< orphan*/  r_baseGloss ; 
 int /*<<< orphan*/  r_baseNormalX ; 
 int /*<<< orphan*/  r_baseNormalY ; 
 int /*<<< orphan*/  r_baseParallax ; 
 int /*<<< orphan*/  r_baseSpecular ; 
 int /*<<< orphan*/  r_buffheight ; 
 int /*<<< orphan*/  r_buffwidth ; 
 int /*<<< orphan*/  r_cameraExposure ; 
 int /*<<< orphan*/  r_clear ; 
 int /*<<< orphan*/  r_colorMipLevels ; 
 int /*<<< orphan*/  r_colorbits ; 
 int /*<<< orphan*/  r_cubeMapping ; 
 int /*<<< orphan*/  r_cubemapSize ; 
 int /*<<< orphan*/  r_customPixelAspect ; 
 int /*<<< orphan*/  r_customheight ; 
 int /*<<< orphan*/  r_customwidth ; 
 int /*<<< orphan*/  r_debugLight ; 
 int /*<<< orphan*/  r_debugSort ; 
 int /*<<< orphan*/  r_debugSurface ; 
 int /*<<< orphan*/  r_deluxeMapping ; 
 int /*<<< orphan*/  r_deluxeSpecular ; 
 int /*<<< orphan*/  r_depthPrepass ; 
 int /*<<< orphan*/  r_depthbits ; 
 int /*<<< orphan*/  r_detailTextures ; 
 int /*<<< orphan*/  r_directedScale ; 
 int /*<<< orphan*/  r_displayRefresh ; 
 int /*<<< orphan*/  r_dlightBacks ; 
 int /*<<< orphan*/  r_dlightMode ; 
 int /*<<< orphan*/  r_drawBuffer ; 
 int /*<<< orphan*/  r_drawSun ; 
 int /*<<< orphan*/  r_drawSunRays ; 
 int /*<<< orphan*/  r_drawentities ; 
 int /*<<< orphan*/  r_drawworld ; 
 int /*<<< orphan*/  r_dynamiclight ; 
 int /*<<< orphan*/  r_ext_compiled_vertex_array ; 
 int /*<<< orphan*/  r_ext_compressed_textures ; 
 int /*<<< orphan*/  r_ext_direct_state_access ; 
 int /*<<< orphan*/  r_ext_framebuffer_multisample ; 
 int /*<<< orphan*/  r_ext_framebuffer_object ; 
 int /*<<< orphan*/  r_ext_max_anisotropy ; 
 int /*<<< orphan*/  r_ext_multisample ; 
 int /*<<< orphan*/  r_ext_multitexture ; 
 int /*<<< orphan*/  r_ext_texture_env_add ; 
 int /*<<< orphan*/  r_ext_texture_filter_anisotropic ; 
 int /*<<< orphan*/  r_ext_texture_float ; 
 int /*<<< orphan*/  r_externalGLSL ; 
 int /*<<< orphan*/  r_facePlaneCull ; 
 int /*<<< orphan*/  r_fastsky ; 
 int /*<<< orphan*/  r_finish ; 
 int /*<<< orphan*/  r_flareCoeff ; 
 int /*<<< orphan*/  r_flareFade ; 
 int /*<<< orphan*/  r_flareSize ; 
 int /*<<< orphan*/  r_flares ; 
 int /*<<< orphan*/  r_floatLightmap ; 
 int /*<<< orphan*/  r_forceAutoExposure ; 
 int /*<<< orphan*/  r_forceAutoExposureMax ; 
 int /*<<< orphan*/  r_forceAutoExposureMin ; 
 int /*<<< orphan*/  r_forceSun ; 
 int /*<<< orphan*/  r_forceSunAmbientScale ; 
 int /*<<< orphan*/  r_forceSunLightScale ; 
 int /*<<< orphan*/  r_forceToneMap ; 
 int /*<<< orphan*/  r_forceToneMapAvg ; 
 int /*<<< orphan*/  r_forceToneMapMax ; 
 int /*<<< orphan*/  r_forceToneMapMin ; 
 int /*<<< orphan*/  r_fullbright ; 
 int /*<<< orphan*/  r_fullscreen ; 
 int /*<<< orphan*/  r_gamma ; 
 int /*<<< orphan*/  r_genNormalMaps ; 
 int /*<<< orphan*/  r_glossType ; 
 int /*<<< orphan*/  r_greyscale ; 
 int /*<<< orphan*/  r_hdr ; 
 int /*<<< orphan*/  r_ignore ; 
 int /*<<< orphan*/  r_ignoreDstAlpha ; 
 int /*<<< orphan*/  r_ignoreGLErrors ; 
 int /*<<< orphan*/  r_ignorehwgamma ; 
 int /*<<< orphan*/  r_imageUpsample ; 
 int /*<<< orphan*/  r_imageUpsampleMaxSize ; 
 int /*<<< orphan*/  r_imageUpsampleType ; 
 int /*<<< orphan*/  r_inGameVideo ; 
 int /*<<< orphan*/  r_intensity ; 
 int /*<<< orphan*/  r_lightmap ; 
 int /*<<< orphan*/  r_lockpvs ; 
 int /*<<< orphan*/  r_lodCurveError ; 
 int /*<<< orphan*/  r_lodbias ; 
 int /*<<< orphan*/  r_lodscale ; 
 int /*<<< orphan*/  r_logFile ; 
 int /*<<< orphan*/  r_mapOverBrightBits ; 
 int /*<<< orphan*/  r_marksOnTriangleMeshes ; 
 int /*<<< orphan*/  r_maxpolys ; 
 int /*<<< orphan*/  r_maxpolyverts ; 
 int /*<<< orphan*/  r_measureOverdraw ; 
 int /*<<< orphan*/  r_mergeLightmaps ; 
 int /*<<< orphan*/  r_mode ; 
 int /*<<< orphan*/  r_monolightmaps ; 
 int /*<<< orphan*/  r_nobind ; 
 int /*<<< orphan*/  r_noborder ; 
 int /*<<< orphan*/  r_nocull ; 
 int /*<<< orphan*/  r_nocurves ; 
 int /*<<< orphan*/  r_noportals ; 
 int /*<<< orphan*/  r_norefresh ; 
 int /*<<< orphan*/  r_normalMapping ; 
 int /*<<< orphan*/  r_novis ; 
 int /*<<< orphan*/  r_offsetFactor ; 
 int /*<<< orphan*/  r_offsetUnits ; 
 int /*<<< orphan*/  r_overBrightBits ; 
 int /*<<< orphan*/  r_parallaxMapping ; 
 int /*<<< orphan*/  r_pbr ; 
 int /*<<< orphan*/  r_picmip ; 
 int /*<<< orphan*/  r_portalOnly ; 
 int /*<<< orphan*/  r_postProcess ; 
 int /*<<< orphan*/  r_printShaders ; 
 int /*<<< orphan*/  r_pshadowDist ; 
 int /*<<< orphan*/  r_railCoreWidth ; 
 int /*<<< orphan*/  r_railSegmentLength ; 
 int /*<<< orphan*/  r_railWidth ; 
 int /*<<< orphan*/  r_roundImagesDown ; 
 int /*<<< orphan*/  r_saveFontData ; 
 int /*<<< orphan*/  r_screenshotJpegQuality ; 
 int /*<<< orphan*/  r_shadowBlur ; 
 int /*<<< orphan*/  r_shadowCascadeZBias ; 
 int /*<<< orphan*/  r_shadowCascadeZFar ; 
 int /*<<< orphan*/  r_shadowCascadeZNear ; 
 int /*<<< orphan*/  r_shadowFilter ; 
 int /*<<< orphan*/  r_shadowMapSize ; 
 int /*<<< orphan*/  r_shadows ; 
 int /*<<< orphan*/  r_showImages ; 
 int /*<<< orphan*/  r_showcluster ; 
 int /*<<< orphan*/  r_shownormals ; 
 int /*<<< orphan*/  r_showsky ; 
 int /*<<< orphan*/  r_showtris ; 
 int /*<<< orphan*/  r_simpleMipMaps ; 
 int /*<<< orphan*/  r_singleShader ; 
 int /*<<< orphan*/  r_skipBackEnd ; 
 int /*<<< orphan*/  r_specularMapping ; 
 int /*<<< orphan*/  r_speeds ; 
 int /*<<< orphan*/  r_ssao ; 
 int /*<<< orphan*/  r_stencilbits ; 
 int /*<<< orphan*/  r_stereoEnabled ; 
 int /*<<< orphan*/  r_stereoSeparation ; 
 int /*<<< orphan*/  r_subdivisions ; 
 int /*<<< orphan*/  r_sunShadows ; 
 int /*<<< orphan*/  r_sunlightMode ; 
 int /*<<< orphan*/  r_swapInterval ; 
 int /*<<< orphan*/  r_textureMaxSize ; 
 int /*<<< orphan*/  r_textureMode ; 
 int /*<<< orphan*/  r_texturebits ; 
 int /*<<< orphan*/  r_toneMap ; 
 int /*<<< orphan*/  r_uiFullScreen ; 
 int /*<<< orphan*/  r_verbose ; 
 int /*<<< orphan*/  r_vertFlipBuffer ; 
 int /*<<< orphan*/  r_vertexLight ; 
 int /*<<< orphan*/  r_znear ; 
 int /*<<< orphan*/  r_zproj ; 
 TYPE_1__ ri ; 
 int /*<<< orphan*/  stub1 (char*,char*,int) ; 
 int /*<<< orphan*/  stub10 (char*,char*,int) ; 
 int /*<<< orphan*/  stub100 (char*,char*,int) ; 
 int /*<<< orphan*/  stub101 (char*,char*,int) ; 
 int /*<<< orphan*/  stub102 (int /*<<< orphan*/ ,float,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub103 (char*,char*,int) ; 
 int /*<<< orphan*/  stub104 (char*,char*,int) ; 
 int /*<<< orphan*/  stub105 (char*,char*,int) ; 
 int /*<<< orphan*/  stub106 (char*,char*,int) ; 
 int /*<<< orphan*/  stub107 (char*,char*,int) ; 
 int /*<<< orphan*/  stub108 (char*,char*,int) ; 
 int /*<<< orphan*/  stub109 (char*,char*,int) ; 
 int /*<<< orphan*/  stub11 (char*,char*,int) ; 
 int /*<<< orphan*/  stub110 (char*,char*,int) ; 
 int /*<<< orphan*/  stub111 (char*,char*,int) ; 
 int /*<<< orphan*/  stub112 (char*,char*,int) ; 
 int /*<<< orphan*/  stub113 (char*,char*,int) ; 
 int /*<<< orphan*/  stub114 (char*,char*,int) ; 
 int /*<<< orphan*/  stub115 (char*,char*,int) ; 
 int /*<<< orphan*/  stub116 (char*,char*,int) ; 
 int /*<<< orphan*/  stub117 (char*,char*,int) ; 
 int /*<<< orphan*/  stub118 (char*,char*,int) ; 
 int /*<<< orphan*/  stub119 (char*,char*,int) ; 
 int /*<<< orphan*/  stub12 (char*,char*,int) ; 
 int /*<<< orphan*/  stub120 (char*,char*,int) ; 
 int /*<<< orphan*/  stub121 (char*,char*,int) ; 
 int /*<<< orphan*/  stub122 (char*,char*,int) ; 
 int /*<<< orphan*/  stub123 (char*,char*,int) ; 
 int /*<<< orphan*/  stub124 (char*,char*,int) ; 
 int /*<<< orphan*/  stub125 (char*,char*,int) ; 
 int /*<<< orphan*/  stub126 (char*,char*,int) ; 
 int /*<<< orphan*/  stub127 (char*,char*,int) ; 
 int /*<<< orphan*/  stub128 (char*,char*,int) ; 
 int /*<<< orphan*/  stub129 (char*,char*,int) ; 
 int /*<<< orphan*/  stub13 (char*,char*,int) ; 
 int /*<<< orphan*/  stub130 (char*,char*,int) ; 
 int /*<<< orphan*/  stub131 (char*,char*,int) ; 
 int /*<<< orphan*/  stub132 (char*,char*,int) ; 
 int /*<<< orphan*/  stub133 (char*,char*,int) ; 
 int /*<<< orphan*/  stub134 (char*,char*,int) ; 
 int /*<<< orphan*/  stub135 (char*,char*,int) ; 
 int /*<<< orphan*/  stub136 (char*,char*,int) ; 
 int /*<<< orphan*/  stub137 (char*,char*,int) ; 
 int /*<<< orphan*/  stub138 (char*,char*,int) ; 
 int /*<<< orphan*/  stub139 (char*,char*,int) ; 
 int /*<<< orphan*/  stub14 (char*,char*,int) ; 
 int /*<<< orphan*/  stub140 (char*,char*,int) ; 
 int /*<<< orphan*/  stub141 (char*,char*,int) ; 
 int /*<<< orphan*/  stub142 (char*,char*,int) ; 
 int /*<<< orphan*/  stub143 (char*,char*,int) ; 
 int /*<<< orphan*/  stub144 (char*,char*,int) ; 
 int /*<<< orphan*/  stub145 (char*,char*,int) ; 
 int /*<<< orphan*/  stub146 (char*,char*,int) ; 
 int /*<<< orphan*/  stub147 (char*,char*,int) ; 
 int /*<<< orphan*/  stub148 (char*,char*,int) ; 
 int /*<<< orphan*/  stub149 (char*,char*,int) ; 
 int /*<<< orphan*/  stub15 (char*,char*,int) ; 
 int /*<<< orphan*/  stub150 (char*,char*,int) ; 
 int /*<<< orphan*/  stub151 (char*,char*,int) ; 
 int /*<<< orphan*/  stub152 (char*,char*,int) ; 
 int /*<<< orphan*/  stub153 (char*,char*,int) ; 
 int /*<<< orphan*/  stub154 (char*,char*,int) ; 
 int /*<<< orphan*/  stub155 (char*,char*,int) ; 
 int /*<<< orphan*/  stub156 (char*,char*,int) ; 
 int /*<<< orphan*/  stub157 (char*,char*,int) ; 
 int /*<<< orphan*/  stub158 (char*,char*,int) ; 
 int /*<<< orphan*/  stub159 (char*,char*,int) ; 
 int /*<<< orphan*/  stub16 (char*,char*,int) ; 
 int /*<<< orphan*/  stub160 (char*,char*,int) ; 
 int /*<<< orphan*/  stub161 (char*,char*,int) ; 
 int /*<<< orphan*/  stub162 (char*,char*,int) ; 
 int /*<<< orphan*/  stub163 (char*,char*,int) ; 
 int /*<<< orphan*/  stub164 (char*,char*,int) ; 
 int /*<<< orphan*/  stub165 (char*,char*,int) ; 
 int /*<<< orphan*/  stub166 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub167 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub168 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub169 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub17 (int /*<<< orphan*/ ,float,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub170 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub171 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub172 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub173 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub174 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub175 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub176 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub18 (char*,char*,int) ; 
 int /*<<< orphan*/  stub19 (char*,char*,int) ; 
 int /*<<< orphan*/  stub2 (char*,char*,int) ; 
 int /*<<< orphan*/  stub20 (char*,char*,int) ; 
 int /*<<< orphan*/  stub21 (char*,char*,int) ; 
 int /*<<< orphan*/  stub22 (char*,char*,int) ; 
 int /*<<< orphan*/  stub23 (char*,char*,int) ; 
 int /*<<< orphan*/  stub24 (int /*<<< orphan*/ ,float,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub25 (char*,char*,int) ; 
 int /*<<< orphan*/  stub26 (char*,char*,int) ; 
 int /*<<< orphan*/  stub27 (char*,char*,int) ; 
 int /*<<< orphan*/  stub28 (char*,char*,int) ; 
 int /*<<< orphan*/  stub29 (char*,char*,int) ; 
 int /*<<< orphan*/  stub3 (char*,char*,int) ; 
 int /*<<< orphan*/  stub30 (char*,char*,int) ; 
 int /*<<< orphan*/  stub31 (char*,char*,int) ; 
 int /*<<< orphan*/  stub32 (char*,char*,int) ; 
 int /*<<< orphan*/  stub33 (char*,char*,int) ; 
 int /*<<< orphan*/  stub34 (char*,char*,int) ; 
 int /*<<< orphan*/  stub35 (char*,char*,int) ; 
 int /*<<< orphan*/  stub36 (char*,char*,int) ; 
 int /*<<< orphan*/  stub37 (char*,char*,int) ; 
 int /*<<< orphan*/  stub38 (char*,char*,int) ; 
 int /*<<< orphan*/  stub39 (char*,char*,int) ; 
 int /*<<< orphan*/  stub4 (char*,char*,int) ; 
 int /*<<< orphan*/  stub40 (char*,char*,int) ; 
 int /*<<< orphan*/  stub41 (int /*<<< orphan*/ ,float,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub42 (char*,char*,int) ; 
 int /*<<< orphan*/  stub43 (char*,char*,int) ; 
 int /*<<< orphan*/  stub44 (char*,char*,int) ; 
 int /*<<< orphan*/  stub45 (char*,char*,int) ; 
 int /*<<< orphan*/  stub46 (char*,char*,int) ; 
 int /*<<< orphan*/  stub47 (char*,char*,int) ; 
 int /*<<< orphan*/  stub48 (char*,char*,int) ; 
 int /*<<< orphan*/  stub49 (char*,char*,int) ; 
 int /*<<< orphan*/  stub5 (char*,char*,int) ; 
 int /*<<< orphan*/  stub50 (char*,char*,int) ; 
 int /*<<< orphan*/  stub51 (char*,char*,int) ; 
 int /*<<< orphan*/  stub52 (char*,char*,int) ; 
 int /*<<< orphan*/  stub53 (char*,char*,int) ; 
 int /*<<< orphan*/  stub54 (char*,char*,int) ; 
 int /*<<< orphan*/  stub55 (char*,char*,int) ; 
 int /*<<< orphan*/  stub56 (char*,char*,int) ; 
 int /*<<< orphan*/  stub57 (char*,char*,int) ; 
 int /*<<< orphan*/  stub58 (char*,char*,int) ; 
 int /*<<< orphan*/  stub59 (char*,char*,int) ; 
 int /*<<< orphan*/  stub6 (char*,char*,int) ; 
 int /*<<< orphan*/  stub60 (char*,char*,int) ; 
 int /*<<< orphan*/  stub61 (char*,char*,int) ; 
 int /*<<< orphan*/  stub62 (char*,char*,int) ; 
 int /*<<< orphan*/  stub63 (char*,char*,int) ; 
 int /*<<< orphan*/  stub64 (char*,char*,int) ; 
 int /*<<< orphan*/  stub65 (char*,char*,int) ; 
 int /*<<< orphan*/  stub66 (char*,char*,int) ; 
 int /*<<< orphan*/  stub67 (char*,char*,int) ; 
 int /*<<< orphan*/  stub68 (char*,char*,int) ; 
 int /*<<< orphan*/  stub69 (char*,char*,int) ; 
 int /*<<< orphan*/  stub7 (char*,char*,int) ; 
 int /*<<< orphan*/  stub70 (char*,char*,int) ; 
 int /*<<< orphan*/  stub71 (char*,char*,int) ; 
 int /*<<< orphan*/  stub72 (char*,char*,int) ; 
 int /*<<< orphan*/  stub73 (char*,char*,int) ; 
 int /*<<< orphan*/  stub74 (char*,char*,int) ; 
 int /*<<< orphan*/  stub75 (char*,char*,int) ; 
 int /*<<< orphan*/  stub76 (char*,char*,int) ; 
 int /*<<< orphan*/  stub77 (char*,char*,int) ; 
 int /*<<< orphan*/  stub78 (char*,char*,int) ; 
 int /*<<< orphan*/  stub79 (char*,char*,int) ; 
 int /*<<< orphan*/  stub8 (char*,char*,int) ; 
 int /*<<< orphan*/  stub80 (char*,char*,int) ; 
 int /*<<< orphan*/  stub81 (char*,char*,int) ; 
 int /*<<< orphan*/  stub82 (char*,char*,int) ; 
 int /*<<< orphan*/  stub83 (char*,char*,int) ; 
 int /*<<< orphan*/  stub84 (char*,char*,int) ; 
 int /*<<< orphan*/  stub85 (char*,char*,int) ; 
 int /*<<< orphan*/  stub86 (char*,char*,int) ; 
 int /*<<< orphan*/  stub87 (char*,char*,int) ; 
 int /*<<< orphan*/  stub88 (char*,char*,int) ; 
 int /*<<< orphan*/  stub89 (char*,char*,int) ; 
 int /*<<< orphan*/  stub9 (char*,char*,int) ; 
 int /*<<< orphan*/  stub90 (char*,char*,int) ; 
 int /*<<< orphan*/  stub91 (char*,char*,int) ; 
 int /*<<< orphan*/  stub92 (char*,char*,int) ; 
 int /*<<< orphan*/  stub93 (int /*<<< orphan*/ ,float,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub94 (char*,char*,int) ; 
 int /*<<< orphan*/  stub95 (char*,char*,int) ; 
 int /*<<< orphan*/  stub96 (char*,char*,int) ; 
 int /*<<< orphan*/  stub97 (char*,char*,int) ; 
 int /*<<< orphan*/  stub98 (char*,char*,int) ; 
 int /*<<< orphan*/  stub99 (char*,char*,int) ; 
 char* va (char*,int /*<<< orphan*/ ) ; 

void R_Register( void ) 
{
	#ifdef USE_RENDERER_DLOPEN
	com_altivec = ri.Cvar_Get("com_altivec", "1", CVAR_ARCHIVE);
	#endif	

	//
	// latched and archived variables
	//
	r_allowExtensions = ri.Cvar_Get( "r_allowExtensions", "1", CVAR_ARCHIVE | CVAR_LATCH );
	r_ext_compressed_textures = ri.Cvar_Get( "r_ext_compressed_textures", "0", CVAR_ARCHIVE | CVAR_LATCH );
	r_ext_multitexture = ri.Cvar_Get( "r_ext_multitexture", "1", CVAR_ARCHIVE | CVAR_LATCH );
	r_ext_compiled_vertex_array = ri.Cvar_Get( "r_ext_compiled_vertex_array", "1", CVAR_ARCHIVE | CVAR_LATCH);
	r_ext_texture_env_add = ri.Cvar_Get( "r_ext_texture_env_add", "1", CVAR_ARCHIVE | CVAR_LATCH);

	r_ext_framebuffer_object = ri.Cvar_Get( "r_ext_framebuffer_object", "1", CVAR_ARCHIVE | CVAR_LATCH);
	r_ext_texture_float = ri.Cvar_Get( "r_ext_texture_float", "1", CVAR_ARCHIVE | CVAR_LATCH);
	r_ext_framebuffer_multisample = ri.Cvar_Get( "r_ext_framebuffer_multisample", "0", CVAR_ARCHIVE | CVAR_LATCH);
	r_arb_seamless_cube_map = ri.Cvar_Get( "r_arb_seamless_cube_map", "0", CVAR_ARCHIVE | CVAR_LATCH);
	r_arb_vertex_array_object = ri.Cvar_Get( "r_arb_vertex_array_object", "1", CVAR_ARCHIVE | CVAR_LATCH);
	r_ext_direct_state_access = ri.Cvar_Get("r_ext_direct_state_access", "1", CVAR_ARCHIVE | CVAR_LATCH);

	r_ext_texture_filter_anisotropic = ri.Cvar_Get( "r_ext_texture_filter_anisotropic",
			"0", CVAR_ARCHIVE | CVAR_LATCH );
	r_ext_max_anisotropy = ri.Cvar_Get( "r_ext_max_anisotropy", "2", CVAR_ARCHIVE | CVAR_LATCH );

	r_picmip = ri.Cvar_Get ("r_picmip", "1", CVAR_ARCHIVE | CVAR_LATCH );
	r_roundImagesDown = ri.Cvar_Get ("r_roundImagesDown", "1", CVAR_ARCHIVE | CVAR_LATCH );
	r_colorMipLevels = ri.Cvar_Get ("r_colorMipLevels", "0", CVAR_LATCH );
	ri.Cvar_CheckRange( r_picmip, 0, 16, qtrue );
	r_detailTextures = ri.Cvar_Get( "r_detailtextures", "1", CVAR_ARCHIVE | CVAR_LATCH );
	r_texturebits = ri.Cvar_Get( "r_texturebits", "0", CVAR_ARCHIVE | CVAR_LATCH );
	r_colorbits = ri.Cvar_Get( "r_colorbits", "0", CVAR_ARCHIVE | CVAR_LATCH );
	r_stencilbits = ri.Cvar_Get( "r_stencilbits", "8", CVAR_ARCHIVE | CVAR_LATCH );
	r_depthbits = ri.Cvar_Get( "r_depthbits", "0", CVAR_ARCHIVE | CVAR_LATCH );
	r_ext_multisample = ri.Cvar_Get( "r_ext_multisample", "0", CVAR_ARCHIVE | CVAR_LATCH );
	ri.Cvar_CheckRange( r_ext_multisample, 0, 4, qtrue );
	r_overBrightBits = ri.Cvar_Get ("r_overBrightBits", "1", CVAR_ARCHIVE | CVAR_LATCH );
	r_ignorehwgamma = ri.Cvar_Get( "r_ignorehwgamma", "0", CVAR_ARCHIVE | CVAR_LATCH);
	r_mode = ri.Cvar_Get( "r_mode", "-2", CVAR_ARCHIVE | CVAR_LATCH );
	r_fullscreen = ri.Cvar_Get( "r_fullscreen", "1", CVAR_ARCHIVE );
	r_noborder = ri.Cvar_Get("r_noborder", "0", CVAR_ARCHIVE | CVAR_LATCH);
	r_buffwidth = ri.Cvar_Get( "r_buffwidth", "1600", CVAR_ARCHIVE | CVAR_LATCH );
	r_buffheight = ri.Cvar_Get( "r_buffheight", "1024", CVAR_ARCHIVE | CVAR_LATCH );
	r_customwidth = ri.Cvar_Get( "r_customwidth", "1600", CVAR_ARCHIVE | CVAR_LATCH );
	r_customheight = ri.Cvar_Get( "r_customheight", "1024", CVAR_ARCHIVE | CVAR_LATCH );
	r_customPixelAspect = ri.Cvar_Get( "r_customPixelAspect", "1", CVAR_ARCHIVE | CVAR_LATCH );
	r_simpleMipMaps = ri.Cvar_Get( "r_simpleMipMaps", "1", CVAR_ARCHIVE | CVAR_LATCH );
	r_vertexLight = ri.Cvar_Get( "r_vertexLight", "0", CVAR_ARCHIVE | CVAR_LATCH );
	r_uiFullScreen = ri.Cvar_Get( "r_uifullscreen", "0", 0);
	r_subdivisions = ri.Cvar_Get ("r_subdivisions", "4", CVAR_ARCHIVE | CVAR_LATCH);
	r_stereoEnabled = ri.Cvar_Get( "r_stereoEnabled", "0", CVAR_ARCHIVE | CVAR_LATCH);
	r_greyscale = ri.Cvar_Get("r_greyscale", "0", CVAR_ARCHIVE | CVAR_LATCH);
	ri.Cvar_CheckRange(r_greyscale, 0, 1, qfalse);

	r_externalGLSL = ri.Cvar_Get( "r_externalGLSL", "0", CVAR_LATCH );

	r_hdr = ri.Cvar_Get( "r_hdr", "1", CVAR_ARCHIVE | CVAR_LATCH );
	r_floatLightmap = ri.Cvar_Get( "r_floatLightmap", "0", CVAR_ARCHIVE | CVAR_LATCH );
	r_postProcess = ri.Cvar_Get( "r_postProcess", "1", CVAR_ARCHIVE );

	r_toneMap = ri.Cvar_Get( "r_toneMap", "1", CVAR_ARCHIVE );
	r_forceToneMap = ri.Cvar_Get( "r_forceToneMap", "0", CVAR_CHEAT );
	r_forceToneMapMin = ri.Cvar_Get( "r_forceToneMapMin", "-8.0", CVAR_CHEAT );
	r_forceToneMapAvg = ri.Cvar_Get( "r_forceToneMapAvg", "-2.0", CVAR_CHEAT );
	r_forceToneMapMax = ri.Cvar_Get( "r_forceToneMapMax", "0.0", CVAR_CHEAT );

	r_autoExposure = ri.Cvar_Get( "r_autoExposure", "1", CVAR_ARCHIVE );
	r_forceAutoExposure = ri.Cvar_Get( "r_forceAutoExposure", "0", CVAR_CHEAT );
	r_forceAutoExposureMin = ri.Cvar_Get( "r_forceAutoExposureMin", "-2.0", CVAR_CHEAT );
	r_forceAutoExposureMax = ri.Cvar_Get( "r_forceAutoExposureMax", "2.0", CVAR_CHEAT );

	r_cameraExposure = ri.Cvar_Get( "r_cameraExposure", "1", CVAR_CHEAT );

	r_depthPrepass = ri.Cvar_Get( "r_depthPrepass", "1", CVAR_ARCHIVE );
	r_ssao = ri.Cvar_Get( "r_ssao", "0", CVAR_LATCH | CVAR_ARCHIVE );

	r_normalMapping = ri.Cvar_Get( "r_normalMapping", "1", CVAR_ARCHIVE | CVAR_LATCH );
	r_specularMapping = ri.Cvar_Get( "r_specularMapping", "1", CVAR_ARCHIVE | CVAR_LATCH );
	r_deluxeMapping = ri.Cvar_Get( "r_deluxeMapping", "1", CVAR_ARCHIVE | CVAR_LATCH );
	r_parallaxMapping = ri.Cvar_Get( "r_parallaxMapping", "0", CVAR_ARCHIVE | CVAR_LATCH );
	r_cubeMapping = ri.Cvar_Get( "r_cubeMapping", "0", CVAR_ARCHIVE | CVAR_LATCH );
	r_cubemapSize = ri.Cvar_Get( "r_cubemapSize", "128", CVAR_ARCHIVE | CVAR_LATCH );
	r_deluxeSpecular = ri.Cvar_Get("r_deluxeSpecular", "0.3", CVAR_ARCHIVE | CVAR_LATCH);
	r_pbr = ri.Cvar_Get("r_pbr", "0", CVAR_ARCHIVE | CVAR_LATCH);
	r_baseNormalX = ri.Cvar_Get( "r_baseNormalX", "1.0", CVAR_ARCHIVE | CVAR_LATCH );
	r_baseNormalY = ri.Cvar_Get( "r_baseNormalY", "1.0", CVAR_ARCHIVE | CVAR_LATCH );
	r_baseParallax = ri.Cvar_Get( "r_baseParallax", "0.05", CVAR_ARCHIVE | CVAR_LATCH );
	r_baseSpecular = ri.Cvar_Get( "r_baseSpecular", "0.04", CVAR_ARCHIVE | CVAR_LATCH );
	r_baseGloss = ri.Cvar_Get( "r_baseGloss", "0.3", CVAR_ARCHIVE | CVAR_LATCH );
	r_glossType = ri.Cvar_Get("r_glossType", "1", CVAR_ARCHIVE | CVAR_LATCH);
	r_dlightMode = ri.Cvar_Get( "r_dlightMode", "0", CVAR_ARCHIVE | CVAR_LATCH );
	r_pshadowDist = ri.Cvar_Get( "r_pshadowDist", "128", CVAR_ARCHIVE );
	r_mergeLightmaps = ri.Cvar_Get( "r_mergeLightmaps", "1", CVAR_ARCHIVE | CVAR_LATCH );
	r_imageUpsample = ri.Cvar_Get( "r_imageUpsample", "0", CVAR_ARCHIVE | CVAR_LATCH );
	r_imageUpsampleMaxSize = ri.Cvar_Get( "r_imageUpsampleMaxSize", "1024", CVAR_ARCHIVE | CVAR_LATCH );
	r_imageUpsampleType = ri.Cvar_Get( "r_imageUpsampleType", "1", CVAR_ARCHIVE | CVAR_LATCH );
	r_genNormalMaps = ri.Cvar_Get( "r_genNormalMaps", "0", CVAR_ARCHIVE | CVAR_LATCH );

	r_forceSun = ri.Cvar_Get( "r_forceSun", "0", CVAR_CHEAT );
	r_forceSunLightScale = ri.Cvar_Get( "r_forceSunLightScale", "1.0", CVAR_CHEAT );
	r_forceSunAmbientScale = ri.Cvar_Get( "r_forceSunAmbientScale", "0.5", CVAR_CHEAT );
	r_drawSunRays = ri.Cvar_Get( "r_drawSunRays", "0", CVAR_ARCHIVE | CVAR_LATCH );
	r_sunlightMode = ri.Cvar_Get( "r_sunlightMode", "1", CVAR_ARCHIVE | CVAR_LATCH );

	r_sunShadows = ri.Cvar_Get( "r_sunShadows", "1", CVAR_ARCHIVE | CVAR_LATCH );
	r_shadowFilter = ri.Cvar_Get( "r_shadowFilter", "1", CVAR_ARCHIVE | CVAR_LATCH );
	r_shadowBlur = ri.Cvar_Get("r_shadowBlur", "0", CVAR_ARCHIVE | CVAR_LATCH);
	r_shadowMapSize = ri.Cvar_Get("r_shadowMapSize", "1024", CVAR_ARCHIVE | CVAR_LATCH);
	r_shadowCascadeZNear = ri.Cvar_Get( "r_shadowCascadeZNear", "8", CVAR_ARCHIVE | CVAR_LATCH );
	r_shadowCascadeZFar = ri.Cvar_Get( "r_shadowCascadeZFar", "1024", CVAR_ARCHIVE | CVAR_LATCH );
	r_shadowCascadeZBias = ri.Cvar_Get( "r_shadowCascadeZBias", "0", CVAR_ARCHIVE | CVAR_LATCH );
	r_ignoreDstAlpha = ri.Cvar_Get( "r_ignoreDstAlpha", "1", CVAR_ARCHIVE | CVAR_LATCH );

	//
	// temporary latched variables that can only change over a restart
	//
	r_displayRefresh = ri.Cvar_Get( "r_displayRefresh", "0", CVAR_LATCH );
	ri.Cvar_CheckRange( r_displayRefresh, 0, 200, qtrue );
	r_fullbright = ri.Cvar_Get ("r_fullbright", "0", CVAR_LATCH|CVAR_CHEAT );
	r_mapOverBrightBits = ri.Cvar_Get ("r_mapOverBrightBits", "2", CVAR_LATCH );
	r_intensity = ri.Cvar_Get ("r_intensity", "1", CVAR_LATCH );
	r_singleShader = ri.Cvar_Get ("r_singleShader", "0", CVAR_CHEAT | CVAR_LATCH );

	//
	// archived variables that can change at any time
	//
	r_lodCurveError = ri.Cvar_Get( "r_lodCurveError", "250", CVAR_ARCHIVE|CVAR_CHEAT );
	r_lodbias = ri.Cvar_Get( "r_lodbias", "0", CVAR_ARCHIVE );
	r_flares = ri.Cvar_Get ("r_flares", "0", CVAR_ARCHIVE );
	r_znear = ri.Cvar_Get( "r_znear", "4", CVAR_CHEAT );
	ri.Cvar_CheckRange( r_znear, 0.001f, 200, qfalse );
	r_zproj = ri.Cvar_Get( "r_zproj", "64", CVAR_ARCHIVE );
	r_stereoSeparation = ri.Cvar_Get( "r_stereoSeparation", "64", CVAR_ARCHIVE );
	r_ignoreGLErrors = ri.Cvar_Get( "r_ignoreGLErrors", "1", CVAR_ARCHIVE );
	r_fastsky = ri.Cvar_Get( "r_fastsky", "0", CVAR_ARCHIVE );
	r_inGameVideo = ri.Cvar_Get( "r_inGameVideo", "1", CVAR_ARCHIVE );
	r_drawSun = ri.Cvar_Get( "r_drawSun", "0", CVAR_ARCHIVE );
	r_dynamiclight = ri.Cvar_Get( "r_dynamiclight", "1", CVAR_ARCHIVE );
	r_dlightBacks = ri.Cvar_Get( "r_dlightBacks", "1", CVAR_ARCHIVE );
	r_finish = ri.Cvar_Get ("r_finish", "0", CVAR_ARCHIVE);
	r_textureMode = ri.Cvar_Get( "r_textureMode", "GL_LINEAR_MIPMAP_NEAREST", CVAR_ARCHIVE );
	r_swapInterval = ri.Cvar_Get( "r_swapInterval", "0",
					CVAR_ARCHIVE | CVAR_LATCH );
	r_gamma = ri.Cvar_Get( "r_gamma", "1", CVAR_ARCHIVE );
	r_facePlaneCull = ri.Cvar_Get ("r_facePlaneCull", "1", CVAR_ARCHIVE );

	r_railWidth = ri.Cvar_Get( "r_railWidth", "16", CVAR_ARCHIVE );
	r_railCoreWidth = ri.Cvar_Get( "r_railCoreWidth", "6", CVAR_ARCHIVE );
	r_railSegmentLength = ri.Cvar_Get( "r_railSegmentLength", "32", CVAR_ARCHIVE );

	r_ambientScale = ri.Cvar_Get( "r_ambientScale", "0.6", CVAR_CHEAT );
	r_directedScale = ri.Cvar_Get( "r_directedScale", "1", CVAR_CHEAT );

	r_anaglyphMode = ri.Cvar_Get("r_anaglyphMode", "0", CVAR_ARCHIVE);

	//
	// temporary variables that can change at any time
	//
	r_showImages = ri.Cvar_Get( "r_showImages", "0", CVAR_TEMP );

	r_debugLight = ri.Cvar_Get( "r_debuglight", "0", CVAR_TEMP );
	r_debugSort = ri.Cvar_Get( "r_debugSort", "0", CVAR_CHEAT );
	r_printShaders = ri.Cvar_Get( "r_printShaders", "0", 0 );
	r_saveFontData = ri.Cvar_Get( "r_saveFontData", "0", 0 );

	r_nocurves = ri.Cvar_Get ("r_nocurves", "0", CVAR_CHEAT );
	r_drawworld = ri.Cvar_Get ("r_drawworld", "1", CVAR_CHEAT );
	r_lightmap = ri.Cvar_Get ("r_lightmap", "0", 0 );
	r_portalOnly = ri.Cvar_Get ("r_portalOnly", "0", CVAR_CHEAT );

	r_flareSize = ri.Cvar_Get ("r_flareSize", "40", CVAR_CHEAT);
	r_flareFade = ri.Cvar_Get ("r_flareFade", "7", CVAR_CHEAT);
	r_flareCoeff = ri.Cvar_Get ("r_flareCoeff", FLARE_STDCOEFF, CVAR_CHEAT);

	r_skipBackEnd = ri.Cvar_Get ("r_skipBackEnd", "0", CVAR_CHEAT);

	r_measureOverdraw = ri.Cvar_Get( "r_measureOverdraw", "0", CVAR_CHEAT );
	r_lodscale = ri.Cvar_Get( "r_lodscale", "5", CVAR_CHEAT );
	r_norefresh = ri.Cvar_Get ("r_norefresh", "0", CVAR_CHEAT);
	r_drawentities = ri.Cvar_Get ("r_drawentities", "1", CVAR_CHEAT );
	r_ignore = ri.Cvar_Get( "r_ignore", "1", CVAR_CHEAT );
	r_nocull = ri.Cvar_Get ("r_nocull", "0", CVAR_CHEAT);
	r_novis = ri.Cvar_Get ("r_novis", "0", CVAR_CHEAT);
	r_showcluster = ri.Cvar_Get ("r_showcluster", "0", CVAR_CHEAT);
	r_speeds = ri.Cvar_Get ("r_speeds", "0", CVAR_CHEAT);
	r_verbose = ri.Cvar_Get( "r_verbose", "0", CVAR_CHEAT );
	r_logFile = ri.Cvar_Get( "r_logFile", "0", CVAR_CHEAT );
	r_debugSurface = ri.Cvar_Get ("r_debugSurface", "0", CVAR_CHEAT);
	r_nobind = ri.Cvar_Get ("r_nobind", "0", CVAR_CHEAT);
	r_showtris = ri.Cvar_Get ("r_showtris", "0", CVAR_CHEAT);
	r_showsky = ri.Cvar_Get ("r_showsky", "0", CVAR_CHEAT);
	r_shownormals = ri.Cvar_Get ("r_shownormals", "0", CVAR_CHEAT);
	r_clear = ri.Cvar_Get ("r_clear", "0", CVAR_CHEAT);
	r_offsetFactor = ri.Cvar_Get( "r_offsetfactor", "-1", CVAR_CHEAT );
	r_offsetUnits = ri.Cvar_Get( "r_offsetunits", "-2", CVAR_CHEAT );
	r_drawBuffer = ri.Cvar_Get( "r_drawBuffer", "GL_BACK", CVAR_CHEAT );
	r_lockpvs = ri.Cvar_Get ("r_lockpvs", "0", CVAR_CHEAT);
	r_noportals = ri.Cvar_Get ("r_noportals", "0", CVAR_CHEAT);
	r_shadows = ri.Cvar_Get( "cg_shadows", "1", 0 );

	r_marksOnTriangleMeshes = ri.Cvar_Get("r_marksOnTriangleMeshes", "0", CVAR_ARCHIVE);

	r_aviMotionJpegQuality = ri.Cvar_Get("r_aviMotionJpegQuality", "90", CVAR_ARCHIVE);
	r_screenshotJpegQuality = ri.Cvar_Get("r_screenshotJpegQuality", "90", CVAR_ARCHIVE);

	r_maxpolys = ri.Cvar_Get( "r_maxpolys", va("%d", MAX_POLYS), 0);
	r_maxpolyverts = ri.Cvar_Get( "r_maxpolyverts", va("%d", MAX_POLYVERTS), 0);

	r_monolightmaps = ri.Cvar_Get("r_monolightmaps", "0", CVAR_ARCHIVE | CVAR_LATCH);

	r_textureMaxSize = ri.Cvar_Get( "r_textureMaxSize", "0", CVAR_ARCHIVE | CVAR_LATCH );

	r_vertFlipBuffer = ri.Cvar_Get( "r_vertFlipBuffer", "-1", CVAR_ARCHIVE | CVAR_LATCH );

	// make sure all the commands added here are also
	// removed in R_Shutdown
	ri.Cmd_AddCommand( "imagelist", R_ImageList_f );
	ri.Cmd_AddCommand( "shaderlist", R_ShaderList_f );
	ri.Cmd_AddCommand( "skinlist", R_SkinList_f );
	ri.Cmd_AddCommand( "modellist", R_Modellist_f );
	ri.Cmd_AddCommand( "modelist", R_ModeList_f );
	ri.Cmd_AddCommand( "screenshot", R_ScreenShot_f );
	ri.Cmd_AddCommand( "screenshotJPEG", R_ScreenShotJPEG_f );
	ri.Cmd_AddCommand( "gfxinfo", GfxInfo_f );
	ri.Cmd_AddCommand( "minimize", GLimp_Minimize );
	ri.Cmd_AddCommand( "gfxmeminfo", GfxMemInfo_f );
	ri.Cmd_AddCommand( "exportCubemaps", R_ExportCubemaps_f );
}
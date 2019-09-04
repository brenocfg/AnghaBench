#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {intptr_t (* PC_AddGlobalDefine ) (scalar_t__) ;intptr_t (* PC_LoadSourceHandle ) (scalar_t__) ;intptr_t (* PC_FreeSourceHandle ) (intptr_t) ;intptr_t (* PC_ReadTokenHandle ) (intptr_t,scalar_t__) ;intptr_t (* PC_SourceFileAndLine ) (intptr_t,scalar_t__,scalar_t__) ;} ;
struct TYPE_3__ {intptr_t (* MarkFragments ) (intptr_t,scalar_t__,scalar_t__,intptr_t,scalar_t__,intptr_t,scalar_t__) ;intptr_t (* RegisterModel ) (scalar_t__) ;intptr_t (* RegisterSkin ) (scalar_t__) ;intptr_t (* RegisterShader ) (scalar_t__) ;intptr_t (* RegisterShaderNoMip ) (scalar_t__) ;intptr_t (* LightForPoint ) (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ;intptr_t (* LerpTag ) (scalar_t__,intptr_t,intptr_t,intptr_t,int /*<<< orphan*/ ,scalar_t__) ;intptr_t (* GetEntityToken ) (scalar_t__,intptr_t) ;intptr_t (* inPVS ) (scalar_t__,scalar_t__) ;int /*<<< orphan*/  (* RemapShader ) (scalar_t__,scalar_t__,scalar_t__) ;int /*<<< orphan*/  (* ModelBounds ) (intptr_t,scalar_t__,scalar_t__) ;int /*<<< orphan*/  (* DrawStretchPic ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,intptr_t) ;int /*<<< orphan*/  (* SetColor ) (scalar_t__) ;int /*<<< orphan*/  (* RenderScene ) (scalar_t__) ;int /*<<< orphan*/  (* AddAdditiveLightToScene ) (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* AddLightToScene ) (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* AddPolyToScene ) (intptr_t,intptr_t,scalar_t__,intptr_t) ;int /*<<< orphan*/  (* AddRefEntityToScene ) (scalar_t__) ;int /*<<< orphan*/  (* ClearScene ) () ;int /*<<< orphan*/  (* RegisterFont ) (scalar_t__,intptr_t,scalar_t__) ;int /*<<< orphan*/  (* LoadWorld ) (scalar_t__) ;} ;

/* Variables and functions */
#define  CG_ACOS 227 
#define  CG_ADDCOMMAND 226 
#define  CG_ARGC 225 
#define  CG_ARGS 224 
#define  CG_ARGV 223 
#define  CG_ATAN2 222 
#define  CG_CEIL 221 
#define  CG_CIN_DRAWCINEMATIC 220 
#define  CG_CIN_PLAYCINEMATIC 219 
#define  CG_CIN_RUNCINEMATIC 218 
#define  CG_CIN_SETEXTENTS 217 
#define  CG_CIN_STOPCINEMATIC 216 
#define  CG_CM_BOXTRACE 215 
#define  CG_CM_CAPSULETRACE 214 
#define  CG_CM_INLINEMODEL 213 
#define  CG_CM_LOADMAP 212 
#define  CG_CM_MARKFRAGMENTS 211 
#define  CG_CM_NUMINLINEMODELS 210 
#define  CG_CM_POINTCONTENTS 209 
#define  CG_CM_TEMPBOXMODEL 208 
#define  CG_CM_TEMPCAPSULEMODEL 207 
#define  CG_CM_TRANSFORMEDBOXTRACE 206 
#define  CG_CM_TRANSFORMEDCAPSULETRACE 205 
#define  CG_CM_TRANSFORMEDPOINTCONTENTS 204 
#define  CG_COS 203 
#define  CG_CVAR_REGISTER 202 
#define  CG_CVAR_SET 201 
#define  CG_CVAR_UPDATE 200 
#define  CG_CVAR_VARIABLESTRINGBUFFER 199 
#define  CG_DEEPMIND_CALLBACK 198 
#define  CG_ERROR 197 
#define  CG_FLOOR 196 
#define  CG_FS_FCLOSEFILE 195 
#define  CG_FS_FOPENFILE 194 
#define  CG_FS_READ 193 
#define  CG_FS_SEEK 192 
#define  CG_FS_WRITE 191 
#define  CG_GETCURRENTCMDNUMBER 190 
#define  CG_GETCURRENTSNAPSHOTNUMBER 189 
#define  CG_GETGAMESTATE 188 
#define  CG_GETGLCONFIG 187 
#define  CG_GETSERVERCOMMAND 186 
#define  CG_GETSNAPSHOT 185 
#define  CG_GETUSERCMD 184 
#define  CG_GET_ENTITY_TOKEN 183 
#define  CG_KEY_GETCATCHER 182 
#define  CG_KEY_GETKEY 181 
#define  CG_KEY_ISDOWN 180 
#define  CG_KEY_SETCATCHER 179 
#define  CG_MEMCPY 178 
#define  CG_MEMORY_REMAINING 177 
#define  CG_MEMSET 176 
#define  CG_MILLISECONDS 175 
#define  CG_PC_ADD_GLOBAL_DEFINE 174 
#define  CG_PC_FREE_SOURCE 173 
#define  CG_PC_LOAD_SOURCE 172 
#define  CG_PC_READ_TOKEN 171 
#define  CG_PC_SOURCE_FILE_AND_LINE 170 
#define  CG_PRINT 169 
#define  CG_REAL_TIME 168 
#define  CG_REMOVECOMMAND 167 
#define  CG_R_ADDADDITIVELIGHTTOSCENE 166 
#define  CG_R_ADDLIGHTTOSCENE 165 
#define  CG_R_ADDPOLYSTOSCENE 164 
#define  CG_R_ADDPOLYTOSCENE 163 
#define  CG_R_ADDREFENTITYTOSCENE 162 
#define  CG_R_CLEARSCENE 161 
#define  CG_R_DRAWSTRETCHPIC 160 
#define  CG_R_INPVS 159 
#define  CG_R_LERPTAG 158 
#define  CG_R_LIGHTFORPOINT 157 
#define  CG_R_LOADWORLDMAP 156 
#define  CG_R_MODELBOUNDS 155 
#define  CG_R_REGISTERFONT 154 
#define  CG_R_REGISTERMODEL 153 
#define  CG_R_REGISTERSHADER 152 
#define  CG_R_REGISTERSHADERNOMIP 151 
#define  CG_R_REGISTERSKIN 150 
#define  CG_R_REMAP_SHADER 149 
#define  CG_R_RENDERSCENE 148 
#define  CG_R_SETCOLOR 147 
#define  CG_SENDCLIENTCOMMAND 146 
#define  CG_SENDCONSOLECOMMAND 145 
#define  CG_SETUSERCMDVALUE 144 
#define  CG_SIN 143 
#define  CG_SNAPVECTOR 142 
#define  CG_SQRT 141 
#define  CG_STRNCPY 140 
#define  CG_S_ADDLOOPINGSOUND 139 
#define  CG_S_ADDREALLOOPINGSOUND 138 
#define  CG_S_CLEARLOOPINGSOUNDS 137 
#define  CG_S_REGISTERSOUND 136 
#define  CG_S_RESPATIALIZE 135 
#define  CG_S_STARTBACKGROUNDTRACK 134 
#define  CG_S_STARTLOCALSOUND 133 
#define  CG_S_STARTSOUND 132 
#define  CG_S_STOPBACKGROUNDTRACK 131 
#define  CG_S_STOPLOOPINGSOUND 130 
#define  CG_S_UPDATEENTITYPOSITION 129 
#define  CG_UPDATESCREEN 128 
 int /*<<< orphan*/  CIN_DrawCinematic (intptr_t) ; 
 intptr_t CIN_PlayCinematic (scalar_t__,intptr_t,intptr_t,intptr_t,intptr_t,intptr_t) ; 
 intptr_t CIN_RunCinematic (intptr_t) ; 
 int /*<<< orphan*/  CIN_SetExtents (intptr_t,intptr_t,intptr_t,intptr_t,intptr_t) ; 
 intptr_t CIN_StopCinematic (intptr_t) ; 
 int /*<<< orphan*/  CL_AddCgameCommand (scalar_t__) ; 
 int /*<<< orphan*/  CL_AddReliableCommand (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CL_CM_LoadMap (scalar_t__) ; 
 intptr_t CL_GetCurrentCmdNumber () ; 
 int /*<<< orphan*/  CL_GetCurrentSnapshotNumber (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  CL_GetGameState (scalar_t__) ; 
 int /*<<< orphan*/  CL_GetGlconfig (scalar_t__) ; 
 intptr_t CL_GetServerCommand (intptr_t) ; 
 intptr_t CL_GetSnapshot (intptr_t,scalar_t__) ; 
 intptr_t CL_GetUserCmd (intptr_t,scalar_t__) ; 
 int /*<<< orphan*/  CL_SetUserCmdValue (intptr_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CM_BoxTrace (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,intptr_t,intptr_t,int /*<<< orphan*/ ) ; 
 intptr_t CM_InlineModel (intptr_t) ; 
 intptr_t CM_NumInlineModels () ; 
 intptr_t CM_PointContents (scalar_t__,intptr_t) ; 
 intptr_t CM_TempBoxModel (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CM_TransformedBoxTrace (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,intptr_t,intptr_t,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 intptr_t CM_TransformedPointContents (scalar_t__,intptr_t,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  Cbuf_AddText (scalar_t__) ; 
 intptr_t Cmd_Argc () ; 
 int /*<<< orphan*/  Cmd_ArgsBuffer (scalar_t__,intptr_t) ; 
 int /*<<< orphan*/  Cmd_ArgvBuffer (intptr_t,scalar_t__,intptr_t) ; 
 int /*<<< orphan*/  Cmd_RemoveCommandSafe (scalar_t__) ; 
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  Com_Memcpy (scalar_t__,scalar_t__,intptr_t) ; 
 int /*<<< orphan*/  Com_Memset (scalar_t__,intptr_t,intptr_t) ; 
 int /*<<< orphan*/  Com_Printf (char*,char const*) ; 
 intptr_t Com_RealTime (scalar_t__) ; 
 int /*<<< orphan*/  Cvar_Register (scalar_t__,scalar_t__,scalar_t__,intptr_t) ; 
 int /*<<< orphan*/  Cvar_SetSafe (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  Cvar_Update (scalar_t__) ; 
 int /*<<< orphan*/  Cvar_VariableStringBuffer (scalar_t__,scalar_t__,intptr_t) ; 
 int /*<<< orphan*/  ERR_DROP ; 
 int /*<<< orphan*/  FS_FCloseFile (intptr_t) ; 
 intptr_t FS_FOpenFileByMode (scalar_t__,scalar_t__,intptr_t) ; 
 int /*<<< orphan*/  FS_Read (scalar_t__,intptr_t,intptr_t) ; 
 intptr_t FS_Seek (intptr_t,intptr_t,intptr_t) ; 
 int /*<<< orphan*/  FS_Write (scalar_t__,intptr_t,intptr_t) ; 
 intptr_t FloatAsInt (int /*<<< orphan*/ ) ; 
 intptr_t Hunk_MemoryRemaining () ; 
 intptr_t KEYCATCH_CONSOLE ; 
 intptr_t Key_GetCatcher () ; 
 intptr_t Key_GetKey (scalar_t__) ; 
 intptr_t Key_IsDown (intptr_t) ; 
 int /*<<< orphan*/  Key_SetCatcher (intptr_t) ; 
 int /*<<< orphan*/  Q_SnapVector (scalar_t__) ; 
 int /*<<< orphan*/  Q_acos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCR_UpdateScreen () ; 
 int /*<<< orphan*/  S_AddLoopingSound (intptr_t,scalar_t__,scalar_t__,intptr_t) ; 
 int /*<<< orphan*/  S_AddRealLoopingSound (intptr_t,scalar_t__,scalar_t__,intptr_t) ; 
 int /*<<< orphan*/  S_ClearLoopingSounds (intptr_t) ; 
 intptr_t S_RegisterSound (scalar_t__,intptr_t) ; 
 int /*<<< orphan*/  S_Respatialize (intptr_t,scalar_t__,scalar_t__,intptr_t) ; 
 int /*<<< orphan*/  S_StartBackgroundTrack (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  S_StartLocalSound (intptr_t,intptr_t) ; 
 int /*<<< orphan*/  S_StartSound (scalar_t__,intptr_t,intptr_t,intptr_t) ; 
 int /*<<< orphan*/  S_StopBackgroundTrack () ; 
 int /*<<< orphan*/  S_StopLoopingSound (intptr_t) ; 
 int /*<<< orphan*/  S_UpdateEntityPosition (intptr_t,scalar_t__) ; 
 intptr_t Sys_Milliseconds () ; 
 scalar_t__ VMA (int) ; 
 int /*<<< orphan*/  VMF (int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atan2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* botlib_export ; 
 int /*<<< orphan*/  ceil (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cos (int /*<<< orphan*/ ) ; 
 intptr_t dmlab_callback (intptr_t,intptr_t,intptr_t,intptr_t,intptr_t,intptr_t,intptr_t,intptr_t,intptr_t,intptr_t,intptr_t,intptr_t,intptr_t) ; 
 int /*<<< orphan*/  floor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_1__ re ; 
 int /*<<< orphan*/  sin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqrt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (scalar_t__,scalar_t__,intptr_t) ; 
 intptr_t stub1 (intptr_t,scalar_t__,scalar_t__,intptr_t,scalar_t__,intptr_t,scalar_t__) ; 
 int /*<<< orphan*/  stub10 (intptr_t,intptr_t,scalar_t__,int) ; 
 int /*<<< orphan*/  stub11 (intptr_t,intptr_t,scalar_t__,intptr_t) ; 
 intptr_t stub12 (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub13 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub14 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub15 (scalar_t__) ; 
 int /*<<< orphan*/  stub16 (scalar_t__) ; 
 int /*<<< orphan*/  stub17 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,intptr_t) ; 
 int /*<<< orphan*/  stub18 (intptr_t,scalar_t__,scalar_t__) ; 
 intptr_t stub19 (scalar_t__,intptr_t,intptr_t,intptr_t,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (scalar_t__) ; 
 intptr_t stub20 (scalar_t__) ; 
 intptr_t stub21 (scalar_t__) ; 
 intptr_t stub22 (intptr_t) ; 
 intptr_t stub23 (intptr_t,scalar_t__) ; 
 intptr_t stub24 (intptr_t,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub25 (scalar_t__,scalar_t__,scalar_t__) ; 
 intptr_t stub26 (scalar_t__,intptr_t) ; 
 intptr_t stub27 (scalar_t__,scalar_t__) ; 
 intptr_t stub3 (scalar_t__) ; 
 intptr_t stub4 (scalar_t__) ; 
 intptr_t stub5 (scalar_t__) ; 
 intptr_t stub6 (scalar_t__) ; 
 int /*<<< orphan*/  stub7 (scalar_t__,intptr_t,scalar_t__) ; 
 int /*<<< orphan*/  stub8 () ; 
 int /*<<< orphan*/  stub9 (scalar_t__) ; 

intptr_t CL_CgameSystemCalls( intptr_t *args ) {
	switch( args[0] ) {
	case CG_PRINT:
		Com_Printf( "%s", (const char*)VMA(1) );
		return 0;
	case CG_ERROR:
		Com_Error( ERR_DROP, "%s", (const char*)VMA(1) );
		return 0;
	case CG_MILLISECONDS:
		return Sys_Milliseconds();
	case CG_CVAR_REGISTER:
		Cvar_Register( VMA(1), VMA(2), VMA(3), args[4] ); 
		return 0;
	case CG_CVAR_UPDATE:
		Cvar_Update( VMA(1) );
		return 0;
	case CG_CVAR_SET:
		Cvar_SetSafe( VMA(1), VMA(2) );
		return 0;
	case CG_CVAR_VARIABLESTRINGBUFFER:
		Cvar_VariableStringBuffer( VMA(1), VMA(2), args[3] );
		return 0;
	case CG_ARGC:
		return Cmd_Argc();
	case CG_ARGV:
		Cmd_ArgvBuffer( args[1], VMA(2), args[3] );
		return 0;
	case CG_ARGS:
		Cmd_ArgsBuffer( VMA(1), args[2] );
		return 0;
	case CG_FS_FOPENFILE:
		return FS_FOpenFileByMode( VMA(1), VMA(2), args[3] );
	case CG_FS_READ:
		FS_Read( VMA(1), args[2], args[3] );
		return 0;
	case CG_FS_WRITE:
		FS_Write( VMA(1), args[2], args[3] );
		return 0;
	case CG_FS_FCLOSEFILE:
		FS_FCloseFile( args[1] );
		return 0;
	case CG_FS_SEEK:
		return FS_Seek( args[1], args[2], args[3] );
	case CG_SENDCONSOLECOMMAND:
		Cbuf_AddText( VMA(1) );
		return 0;
	case CG_ADDCOMMAND:
		CL_AddCgameCommand( VMA(1) );
		return 0;
	case CG_REMOVECOMMAND:
		Cmd_RemoveCommandSafe( VMA(1) );
		return 0;
	case CG_SENDCLIENTCOMMAND:
		CL_AddReliableCommand(VMA(1), qfalse);
		return 0;
	case CG_UPDATESCREEN:
		// this is used during lengthy level loading, so pump message loop
//		Com_EventLoop();	// FIXME: if a server restarts here, BAD THINGS HAPPEN!
// We can't call Com_EventLoop here, a restart will crash and this _does_ happen
// if there is a map change while we are downloading at pk3.
// ZOID
		SCR_UpdateScreen();
		return 0;
	case CG_CM_LOADMAP:
		CL_CM_LoadMap( VMA(1) );
		return 0;
	case CG_CM_NUMINLINEMODELS:
		return CM_NumInlineModels();
	case CG_CM_INLINEMODEL:
		return CM_InlineModel( args[1] );
	case CG_CM_TEMPBOXMODEL:
		return CM_TempBoxModel( VMA(1), VMA(2), /*int capsule*/ qfalse );
	case CG_CM_TEMPCAPSULEMODEL:
		return CM_TempBoxModel( VMA(1), VMA(2), /*int capsule*/ qtrue );
	case CG_CM_POINTCONTENTS:
		return CM_PointContents( VMA(1), args[2] );
	case CG_CM_TRANSFORMEDPOINTCONTENTS:
		return CM_TransformedPointContents( VMA(1), args[2], VMA(3), VMA(4) );
	case CG_CM_BOXTRACE:
		CM_BoxTrace( VMA(1), VMA(2), VMA(3), VMA(4), VMA(5), args[6], args[7], /*int capsule*/ qfalse );
		return 0;
	case CG_CM_CAPSULETRACE:
		CM_BoxTrace( VMA(1), VMA(2), VMA(3), VMA(4), VMA(5), args[6], args[7], /*int capsule*/ qtrue );
		return 0;
	case CG_CM_TRANSFORMEDBOXTRACE:
		CM_TransformedBoxTrace( VMA(1), VMA(2), VMA(3), VMA(4), VMA(5), args[6], args[7], VMA(8), VMA(9), /*int capsule*/ qfalse );
		return 0;
	case CG_CM_TRANSFORMEDCAPSULETRACE:
		CM_TransformedBoxTrace( VMA(1), VMA(2), VMA(3), VMA(4), VMA(5), args[6], args[7], VMA(8), VMA(9), /*int capsule*/ qtrue );
		return 0;
	case CG_CM_MARKFRAGMENTS:
		return re.MarkFragments( args[1], VMA(2), VMA(3), args[4], VMA(5), args[6], VMA(7) );
	case CG_S_STARTSOUND:
		S_StartSound( VMA(1), args[2], args[3], args[4] );
		return 0;
	case CG_S_STARTLOCALSOUND:
		S_StartLocalSound( args[1], args[2] );
		return 0;
	case CG_S_CLEARLOOPINGSOUNDS:
		S_ClearLoopingSounds(args[1]);
		return 0;
	case CG_S_ADDLOOPINGSOUND:
		S_AddLoopingSound( args[1], VMA(2), VMA(3), args[4] );
		return 0;
	case CG_S_ADDREALLOOPINGSOUND:
		S_AddRealLoopingSound( args[1], VMA(2), VMA(3), args[4] );
		return 0;
	case CG_S_STOPLOOPINGSOUND:
		S_StopLoopingSound( args[1] );
		return 0;
	case CG_S_UPDATEENTITYPOSITION:
		S_UpdateEntityPosition( args[1], VMA(2) );
		return 0;
	case CG_S_RESPATIALIZE:
		S_Respatialize( args[1], VMA(2), VMA(3), args[4] );
		return 0;
	case CG_S_REGISTERSOUND:
		return S_RegisterSound( VMA(1), args[2] );
	case CG_S_STARTBACKGROUNDTRACK:
		S_StartBackgroundTrack( VMA(1), VMA(2) );
		return 0;
	case CG_R_LOADWORLDMAP:
		re.LoadWorld( VMA(1) );
		return 0; 
	case CG_R_REGISTERMODEL:
		return re.RegisterModel( VMA(1) );
	case CG_R_REGISTERSKIN:
		return re.RegisterSkin( VMA(1) );
	case CG_R_REGISTERSHADER:
		return re.RegisterShader( VMA(1) );
	case CG_R_REGISTERSHADERNOMIP:
		return re.RegisterShaderNoMip( VMA(1) );
	case CG_R_REGISTERFONT:
		re.RegisterFont( VMA(1), args[2], VMA(3));
		return 0;
	case CG_R_CLEARSCENE:
		re.ClearScene();
		return 0;
	case CG_R_ADDREFENTITYTOSCENE:
		re.AddRefEntityToScene( VMA(1) );
		return 0;
	case CG_R_ADDPOLYTOSCENE:
		re.AddPolyToScene( args[1], args[2], VMA(3), 1 );
		return 0;
	case CG_R_ADDPOLYSTOSCENE:
		re.AddPolyToScene( args[1], args[2], VMA(3), args[4] );
		return 0;
	case CG_R_LIGHTFORPOINT:
		return re.LightForPoint( VMA(1), VMA(2), VMA(3), VMA(4) );
	case CG_R_ADDLIGHTTOSCENE:
		re.AddLightToScene( VMA(1), VMF(2), VMF(3), VMF(4), VMF(5) );
		return 0;
	case CG_R_ADDADDITIVELIGHTTOSCENE:
		re.AddAdditiveLightToScene( VMA(1), VMF(2), VMF(3), VMF(4), VMF(5) );
		return 0;
	case CG_R_RENDERSCENE:
		re.RenderScene( VMA(1) );
		return 0;
	case CG_R_SETCOLOR:
		re.SetColor( VMA(1) );
		return 0;
	case CG_R_DRAWSTRETCHPIC:
		re.DrawStretchPic( VMF(1), VMF(2), VMF(3), VMF(4), VMF(5), VMF(6), VMF(7), VMF(8), args[9] );
		return 0;
	case CG_R_MODELBOUNDS:
		re.ModelBounds( args[1], VMA(2), VMA(3) );
		return 0;
	case CG_R_LERPTAG:
		return re.LerpTag( VMA(1), args[2], args[3], args[4], VMF(5), VMA(6) );
	case CG_GETGLCONFIG:
		CL_GetGlconfig( VMA(1) );
		return 0;
	case CG_GETGAMESTATE:
		CL_GetGameState( VMA(1) );
		return 0;
	case CG_GETCURRENTSNAPSHOTNUMBER:
		CL_GetCurrentSnapshotNumber( VMA(1), VMA(2) );
		return 0;
	case CG_GETSNAPSHOT:
		return CL_GetSnapshot( args[1], VMA(2) );
	case CG_GETSERVERCOMMAND:
		return CL_GetServerCommand( args[1] );
	case CG_GETCURRENTCMDNUMBER:
		return CL_GetCurrentCmdNumber();
	case CG_GETUSERCMD:
		return CL_GetUserCmd( args[1], VMA(2) );
	case CG_SETUSERCMDVALUE:
		CL_SetUserCmdValue( args[1], VMF(2) );
		return 0;
	case CG_MEMORY_REMAINING:
		return Hunk_MemoryRemaining();
  case CG_KEY_ISDOWN:
		return Key_IsDown( args[1] );
  case CG_KEY_GETCATCHER:
		return Key_GetCatcher();
  case CG_KEY_SETCATCHER:
		// Don't allow the cgame module to close the console
		Key_SetCatcher( args[1] | ( Key_GetCatcher( ) & KEYCATCH_CONSOLE ) );
    return 0;
  case CG_KEY_GETKEY:
		return Key_GetKey( VMA(1) );



	case CG_MEMSET:
		Com_Memset( VMA(1), args[2], args[3] );
		return 0;
	case CG_MEMCPY:
		Com_Memcpy( VMA(1), VMA(2), args[3] );
		return 0;
	case CG_STRNCPY:
		strncpy( VMA(1), VMA(2), args[3] );
		return args[1];
	case CG_SIN:
		return FloatAsInt( sin( VMF(1) ) );
	case CG_COS:
		return FloatAsInt( cos( VMF(1) ) );
	case CG_ATAN2:
		return FloatAsInt( atan2( VMF(1), VMF(2) ) );
	case CG_SQRT:
		return FloatAsInt( sqrt( VMF(1) ) );
	case CG_FLOOR:
		return FloatAsInt( floor( VMF(1) ) );
	case CG_CEIL:
		return FloatAsInt( ceil( VMF(1) ) );
	case CG_ACOS:
		return FloatAsInt( Q_acos( VMF(1) ) );

	case CG_PC_ADD_GLOBAL_DEFINE:
		return botlib_export->PC_AddGlobalDefine( VMA(1) );
	case CG_PC_LOAD_SOURCE:
		return botlib_export->PC_LoadSourceHandle( VMA(1) );
	case CG_PC_FREE_SOURCE:
		return botlib_export->PC_FreeSourceHandle( args[1] );
	case CG_PC_READ_TOKEN:
		return botlib_export->PC_ReadTokenHandle( args[1], VMA(2) );
	case CG_PC_SOURCE_FILE_AND_LINE:
		return botlib_export->PC_SourceFileAndLine( args[1], VMA(2), VMA(3) );

	case CG_S_STOPBACKGROUNDTRACK:
		S_StopBackgroundTrack();
		return 0;

	case CG_REAL_TIME:
		return Com_RealTime( VMA(1) );
	case CG_SNAPVECTOR:
		Q_SnapVector(VMA(1));
		return 0;

	case CG_CIN_PLAYCINEMATIC:
	  return CIN_PlayCinematic(VMA(1), args[2], args[3], args[4], args[5], args[6]);

	case CG_CIN_STOPCINEMATIC:
	  return CIN_StopCinematic(args[1]);

	case CG_CIN_RUNCINEMATIC:
	  return CIN_RunCinematic(args[1]);

	case CG_CIN_DRAWCINEMATIC:
	  CIN_DrawCinematic(args[1]);
	  return 0;

	case CG_CIN_SETEXTENTS:
	  CIN_SetExtents(args[1], args[2], args[3], args[4], args[5]);
	  return 0;

	case CG_R_REMAP_SHADER:
		re.RemapShader( VMA(1), VMA(2), VMA(3) );
		return 0;

/*
	case CG_LOADCAMERA:
		return loadCamera(VMA(1));

	case CG_STARTCAMERA:
		startCamera(args[1]);
		return 0;

	case CG_GETCAMERAINFO:
		return getCameraInfo(args[1], VMA(2), VMA(3));
*/
	case CG_GET_ENTITY_TOKEN:
		return re.GetEntityToken( VMA(1), args[2] );
	case CG_R_INPVS:
		return re.inPVS( VMA(1), VMA(2) );

	case CG_DEEPMIND_CALLBACK:
		return dmlab_callback( args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8], args[9], args[10], args[11], args[12], args[13] );

	default:
	        assert(0);
		Com_Error( ERR_DROP, "Bad cgame system trap: %ld", (long int) args[0] );
	}
	return 0;
}
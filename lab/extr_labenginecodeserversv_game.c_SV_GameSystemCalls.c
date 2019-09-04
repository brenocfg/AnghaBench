#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {intptr_t (* BotLoadCharacter ) (scalar_t__,int /*<<< orphan*/ ) ;intptr_t (* Characteristic_Integer ) (intptr_t,intptr_t) ;intptr_t (* Characteristic_BInteger ) (intptr_t,intptr_t,intptr_t,intptr_t) ;intptr_t (* BotAllocChatState ) () ;intptr_t (* BotNextConsoleMessage ) (intptr_t,scalar_t__) ;intptr_t (* BotNumConsoleMessages ) (intptr_t) ;intptr_t (* BotNumInitialChats ) (intptr_t,scalar_t__) ;intptr_t (* BotReplyChat ) (intptr_t,scalar_t__,intptr_t,intptr_t,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ;intptr_t (* BotChatLength ) (intptr_t) ;intptr_t (* StringContains ) (scalar_t__,scalar_t__,intptr_t) ;intptr_t (* BotFindMatch ) (scalar_t__,scalar_t__,intptr_t) ;intptr_t (* BotLoadChatFile ) (intptr_t,scalar_t__,scalar_t__) ;intptr_t (* BotGetTopGoal ) (intptr_t,scalar_t__) ;intptr_t (* BotGetSecondGoal ) (intptr_t,scalar_t__) ;intptr_t (* BotChooseLTGItem ) (intptr_t,scalar_t__,scalar_t__,intptr_t) ;intptr_t (* BotChooseNBGItem ) (intptr_t,scalar_t__,scalar_t__,intptr_t,scalar_t__,int /*<<< orphan*/ ) ;intptr_t (* BotTouchingGoal ) (scalar_t__,scalar_t__) ;intptr_t (* BotItemGoalInVisButNotVisible ) (intptr_t,scalar_t__,scalar_t__,scalar_t__) ;intptr_t (* BotGetLevelItemGoal ) (intptr_t,scalar_t__,scalar_t__) ;intptr_t (* BotGetNextCampSpotGoal ) (intptr_t,scalar_t__) ;intptr_t (* BotGetMapLocationGoal ) (scalar_t__,scalar_t__) ;intptr_t (* BotLoadItemWeights ) (intptr_t,scalar_t__) ;intptr_t (* BotAllocGoalState ) (intptr_t) ;intptr_t (* BotMoveInDirection ) (intptr_t,scalar_t__,int /*<<< orphan*/ ,intptr_t) ;intptr_t (* BotReachabilityArea ) (scalar_t__,intptr_t) ;intptr_t (* BotMovementViewTarget ) (intptr_t,scalar_t__,intptr_t,int /*<<< orphan*/ ,scalar_t__) ;intptr_t (* BotPredictVisiblePosition ) (scalar_t__,intptr_t,scalar_t__,intptr_t,scalar_t__) ;intptr_t (* BotAllocMoveState ) () ;intptr_t (* BotChooseBestFightWeapon ) (intptr_t,scalar_t__) ;intptr_t (* BotLoadWeaponWeights ) (intptr_t,scalar_t__) ;intptr_t (* BotAllocWeaponState ) () ;intptr_t (* GeneticParentsAndChildSelection ) (intptr_t,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ;int /*<<< orphan*/  (* BotResetWeaponState ) (intptr_t) ;int /*<<< orphan*/  (* BotFreeWeaponState ) (intptr_t) ;int /*<<< orphan*/  (* BotGetWeaponInfo ) (intptr_t,intptr_t,scalar_t__) ;int /*<<< orphan*/  (* BotInitMoveState ) (intptr_t,scalar_t__) ;int /*<<< orphan*/  (* BotFreeMoveState ) (intptr_t) ;int /*<<< orphan*/  (* BotResetLastAvoidReach ) (intptr_t) ;int /*<<< orphan*/  (* BotResetAvoidReach ) (intptr_t) ;int /*<<< orphan*/  (* BotMoveToGoal ) (scalar_t__,intptr_t,scalar_t__,intptr_t) ;int /*<<< orphan*/  (* BotAddAvoidSpot ) (intptr_t,scalar_t__,int /*<<< orphan*/ ,intptr_t) ;int /*<<< orphan*/  (* BotResetMoveState ) (intptr_t) ;int /*<<< orphan*/  (* BotFreeGoalState ) (intptr_t) ;int /*<<< orphan*/  (* BotMutateGoalFuzzyLogic ) (intptr_t,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* BotSaveGoalFuzzyLogic ) (intptr_t,scalar_t__) ;int /*<<< orphan*/  (* BotInterbreedGoalFuzzyLogic ) (intptr_t,intptr_t,intptr_t) ;int /*<<< orphan*/  (* BotFreeItemWeights ) (intptr_t) ;int /*<<< orphan*/  (* BotUpdateEntityItems ) () ;int /*<<< orphan*/  (* BotInitLevelItems ) () ;int /*<<< orphan*/  (* BotSetAvoidGoalTime ) (intptr_t,intptr_t,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* BotAvoidGoalTime ) (intptr_t,intptr_t) ;int /*<<< orphan*/  (* BotGoalName ) (intptr_t,scalar_t__,intptr_t) ;int /*<<< orphan*/  (* BotDumpGoalStack ) (intptr_t) ;int /*<<< orphan*/  (* BotDumpAvoidGoals ) (intptr_t) ;int /*<<< orphan*/  (* BotEmptyGoalStack ) (intptr_t) ;int /*<<< orphan*/  (* BotPopGoal ) (intptr_t) ;int /*<<< orphan*/  (* BotPushGoal ) (intptr_t,scalar_t__) ;int /*<<< orphan*/  (* BotRemoveFromAvoidGoals ) (intptr_t,intptr_t) ;int /*<<< orphan*/  (* BotResetAvoidGoals ) (intptr_t) ;int /*<<< orphan*/  (* BotResetGoalState ) (intptr_t) ;int /*<<< orphan*/  (* BotSetChatName ) (intptr_t,scalar_t__,intptr_t) ;int /*<<< orphan*/  (* BotSetChatGender ) (intptr_t,intptr_t) ;int /*<<< orphan*/  (* BotReplaceSynonyms ) (scalar_t__,intptr_t) ;int /*<<< orphan*/  (* UnifyWhiteSpaces ) (scalar_t__) ;int /*<<< orphan*/  (* BotMatchVariable ) (scalar_t__,intptr_t,scalar_t__,intptr_t) ;int /*<<< orphan*/  (* BotGetChatMessage ) (intptr_t,scalar_t__,intptr_t) ;int /*<<< orphan*/  (* BotEnterChat ) (intptr_t,intptr_t,intptr_t) ;int /*<<< orphan*/  (* BotInitialChat ) (intptr_t,scalar_t__,intptr_t,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ;int /*<<< orphan*/  (* BotRemoveConsoleMessage ) (intptr_t,intptr_t) ;int /*<<< orphan*/  (* BotQueueConsoleMessage ) (intptr_t,intptr_t,scalar_t__) ;int /*<<< orphan*/  (* BotFreeChatState ) (intptr_t) ;int /*<<< orphan*/  (* Characteristic_String ) (intptr_t,intptr_t,scalar_t__,intptr_t) ;int /*<<< orphan*/  (* Characteristic_BFloat ) (intptr_t,intptr_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* Characteristic_Float ) (intptr_t,intptr_t) ;int /*<<< orphan*/  (* BotFreeCharacter ) (intptr_t) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  (* EA_ResetInput ) (intptr_t) ;int /*<<< orphan*/  (* EA_GetInput ) (intptr_t,int /*<<< orphan*/ ,scalar_t__) ;int /*<<< orphan*/  (* EA_EndRegular ) (intptr_t,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* EA_View ) (intptr_t,scalar_t__) ;int /*<<< orphan*/  (* EA_Move ) (intptr_t,scalar_t__,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* EA_DelayedJump ) (intptr_t) ;int /*<<< orphan*/  (* EA_Jump ) (intptr_t) ;int /*<<< orphan*/  (* EA_SelectWeapon ) (intptr_t,intptr_t) ;int /*<<< orphan*/  (* EA_MoveRight ) (intptr_t) ;int /*<<< orphan*/  (* EA_MoveLeft ) (intptr_t) ;int /*<<< orphan*/  (* EA_MoveBack ) (intptr_t) ;int /*<<< orphan*/  (* EA_MoveForward ) (intptr_t) ;int /*<<< orphan*/  (* EA_MoveDown ) (intptr_t) ;int /*<<< orphan*/  (* EA_MoveUp ) (intptr_t) ;int /*<<< orphan*/  (* EA_Crouch ) (intptr_t) ;int /*<<< orphan*/  (* EA_Respawn ) (intptr_t) ;int /*<<< orphan*/  (* EA_Use ) (intptr_t) ;int /*<<< orphan*/  (* EA_Attack ) (intptr_t) ;int /*<<< orphan*/  (* EA_Talk ) (intptr_t) ;int /*<<< orphan*/  (* EA_Gesture ) (intptr_t) ;int /*<<< orphan*/  (* EA_Action ) (intptr_t,intptr_t) ;int /*<<< orphan*/  (* EA_Command ) (intptr_t,scalar_t__) ;int /*<<< orphan*/  (* EA_SayTeam ) (intptr_t,scalar_t__) ;int /*<<< orphan*/  (* EA_Say ) (intptr_t,scalar_t__) ;} ;
struct TYPE_8__ {intptr_t (* AAS_BBoxAreas ) (scalar_t__,scalar_t__,scalar_t__,intptr_t) ;intptr_t (* AAS_AreaInfo ) (intptr_t,scalar_t__) ;intptr_t (* AAS_AlternativeRouteGoals ) (scalar_t__,intptr_t,scalar_t__,intptr_t,intptr_t,scalar_t__,intptr_t,intptr_t) ;intptr_t (* AAS_Initialized ) () ;intptr_t (* AAS_PointAreaNum ) (scalar_t__) ;intptr_t (* AAS_PointReachabilityAreaIndex ) (scalar_t__) ;intptr_t (* AAS_TraceAreas ) (scalar_t__,scalar_t__,scalar_t__,scalar_t__,intptr_t) ;intptr_t (* AAS_PointContents ) (scalar_t__) ;intptr_t (* AAS_NextBSPEntity ) (intptr_t) ;intptr_t (* AAS_ValueForBSPEpairKey ) (intptr_t,scalar_t__,scalar_t__,intptr_t) ;intptr_t (* AAS_VectorForBSPEpairKey ) (intptr_t,scalar_t__,scalar_t__) ;intptr_t (* AAS_FloatForBSPEpairKey ) (intptr_t,scalar_t__,scalar_t__) ;intptr_t (* AAS_IntForBSPEpairKey ) (intptr_t,scalar_t__,scalar_t__) ;intptr_t (* AAS_AreaReachability ) (intptr_t) ;intptr_t (* AAS_AreaTravelTimeToGoalArea ) (intptr_t,scalar_t__,intptr_t,intptr_t) ;intptr_t (* AAS_EnableRoutingArea ) (intptr_t,intptr_t) ;intptr_t (* AAS_PredictRoute ) (scalar_t__,intptr_t,scalar_t__,intptr_t,intptr_t,intptr_t,intptr_t,intptr_t,intptr_t,intptr_t,intptr_t) ;intptr_t (* AAS_Swimming ) (scalar_t__) ;intptr_t (* AAS_PredictClientMovement ) (scalar_t__,intptr_t,scalar_t__,intptr_t,intptr_t,scalar_t__,scalar_t__,intptr_t,intptr_t,int /*<<< orphan*/ ,intptr_t,intptr_t,intptr_t) ;int /*<<< orphan*/  (* AAS_Time ) () ;int /*<<< orphan*/  (* AAS_PresenceTypeBoundingBox ) (intptr_t,scalar_t__,scalar_t__) ;int /*<<< orphan*/  (* AAS_EntityInfo ) (intptr_t,scalar_t__) ;} ;
struct TYPE_14__ {intptr_t (* BotLibVarSet ) (scalar_t__,scalar_t__) ;intptr_t (* BotLibVarGet ) (scalar_t__,scalar_t__,intptr_t) ;intptr_t (* PC_AddGlobalDefine ) (scalar_t__) ;intptr_t (* PC_LoadSourceHandle ) (scalar_t__) ;intptr_t (* PC_FreeSourceHandle ) (intptr_t) ;intptr_t (* PC_ReadTokenHandle ) (intptr_t,scalar_t__) ;intptr_t (* PC_SourceFileAndLine ) (intptr_t,scalar_t__,scalar_t__) ;intptr_t (* BotLibStartFrame ) (int /*<<< orphan*/ ) ;intptr_t (* BotLibLoadMap ) (scalar_t__) ;intptr_t (* BotLibUpdateEntity ) (intptr_t,scalar_t__) ;intptr_t (* Test ) (intptr_t,scalar_t__,scalar_t__,scalar_t__) ;TYPE_3__ ai; TYPE_2__ ea; TYPE_1__ aas; } ;
struct TYPE_13__ {int /*<<< orphan*/  entityParsePoint; } ;
struct TYPE_12__ {int integer; } ;
struct TYPE_11__ {int /*<<< orphan*/ * clients; } ;

/* Variables and functions */
 int /*<<< orphan*/  AngleVectors (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
#define  BOTLIB_AAS_ALTERNATIVE_ROUTE_GOAL 323 
#define  BOTLIB_AAS_AREA_INFO 322 
#define  BOTLIB_AAS_AREA_REACHABILITY 321 
#define  BOTLIB_AAS_AREA_TRAVEL_TIME_TO_GOAL_AREA 320 
#define  BOTLIB_AAS_BBOX_AREAS 319 
#define  BOTLIB_AAS_ENABLE_ROUTING_AREA 318 
#define  BOTLIB_AAS_ENTITY_INFO 317 
#define  BOTLIB_AAS_FLOAT_FOR_BSP_EPAIR_KEY 316 
#define  BOTLIB_AAS_INITIALIZED 315 
#define  BOTLIB_AAS_INT_FOR_BSP_EPAIR_KEY 314 
#define  BOTLIB_AAS_NEXT_BSP_ENTITY 313 
#define  BOTLIB_AAS_POINT_AREA_NUM 312 
#define  BOTLIB_AAS_POINT_CONTENTS 311 
#define  BOTLIB_AAS_POINT_REACHABILITY_AREA_INDEX 310 
#define  BOTLIB_AAS_PREDICT_CLIENT_MOVEMENT 309 
#define  BOTLIB_AAS_PREDICT_ROUTE 308 
#define  BOTLIB_AAS_PRESENCE_TYPE_BOUNDING_BOX 307 
#define  BOTLIB_AAS_SWIMMING 306 
#define  BOTLIB_AAS_TIME 305 
#define  BOTLIB_AAS_TRACE_AREAS 304 
#define  BOTLIB_AAS_VALUE_FOR_BSP_EPAIR_KEY 303 
#define  BOTLIB_AAS_VECTOR_FOR_BSP_EPAIR_KEY 302 
#define  BOTLIB_AI_ADD_AVOID_SPOT 301 
#define  BOTLIB_AI_ALLOC_CHAT_STATE 300 
#define  BOTLIB_AI_ALLOC_GOAL_STATE 299 
#define  BOTLIB_AI_ALLOC_MOVE_STATE 298 
#define  BOTLIB_AI_ALLOC_WEAPON_STATE 297 
#define  BOTLIB_AI_AVOID_GOAL_TIME 296 
#define  BOTLIB_AI_CHARACTERISTIC_BFLOAT 295 
#define  BOTLIB_AI_CHARACTERISTIC_BINTEGER 294 
#define  BOTLIB_AI_CHARACTERISTIC_FLOAT 293 
#define  BOTLIB_AI_CHARACTERISTIC_INTEGER 292 
#define  BOTLIB_AI_CHARACTERISTIC_STRING 291 
#define  BOTLIB_AI_CHAT_LENGTH 290 
#define  BOTLIB_AI_CHOOSE_BEST_FIGHT_WEAPON 289 
#define  BOTLIB_AI_CHOOSE_LTG_ITEM 288 
#define  BOTLIB_AI_CHOOSE_NBG_ITEM 287 
#define  BOTLIB_AI_DUMP_AVOID_GOALS 286 
#define  BOTLIB_AI_DUMP_GOAL_STACK 285 
#define  BOTLIB_AI_EMPTY_GOAL_STACK 284 
#define  BOTLIB_AI_ENTER_CHAT 283 
#define  BOTLIB_AI_FIND_MATCH 282 
#define  BOTLIB_AI_FREE_CHARACTER 281 
#define  BOTLIB_AI_FREE_CHAT_STATE 280 
#define  BOTLIB_AI_FREE_GOAL_STATE 279 
#define  BOTLIB_AI_FREE_ITEM_WEIGHTS 278 
#define  BOTLIB_AI_FREE_MOVE_STATE 277 
#define  BOTLIB_AI_FREE_WEAPON_STATE 276 
#define  BOTLIB_AI_GENETIC_PARENTS_AND_CHILD_SELECTION 275 
#define  BOTLIB_AI_GET_CHAT_MESSAGE 274 
#define  BOTLIB_AI_GET_LEVEL_ITEM_GOAL 273 
#define  BOTLIB_AI_GET_MAP_LOCATION_GOAL 272 
#define  BOTLIB_AI_GET_NEXT_CAMP_SPOT_GOAL 271 
#define  BOTLIB_AI_GET_SECOND_GOAL 270 
#define  BOTLIB_AI_GET_TOP_GOAL 269 
#define  BOTLIB_AI_GET_WEAPON_INFO 268 
#define  BOTLIB_AI_GOAL_NAME 267 
#define  BOTLIB_AI_INITIAL_CHAT 266 
#define  BOTLIB_AI_INIT_LEVEL_ITEMS 265 
#define  BOTLIB_AI_INIT_MOVE_STATE 264 
#define  BOTLIB_AI_INTERBREED_GOAL_FUZZY_LOGIC 263 
#define  BOTLIB_AI_ITEM_GOAL_IN_VIS_BUT_NOT_VISIBLE 262 
#define  BOTLIB_AI_LOAD_CHARACTER 261 
#define  BOTLIB_AI_LOAD_CHAT_FILE 260 
#define  BOTLIB_AI_LOAD_ITEM_WEIGHTS 259 
#define  BOTLIB_AI_LOAD_WEAPON_WEIGHTS 258 
#define  BOTLIB_AI_MATCH_VARIABLE 257 
#define  BOTLIB_AI_MOVEMENT_VIEW_TARGET 256 
#define  BOTLIB_AI_MOVE_IN_DIRECTION 255 
#define  BOTLIB_AI_MOVE_TO_GOAL 254 
#define  BOTLIB_AI_MUTATE_GOAL_FUZZY_LOGIC 253 
#define  BOTLIB_AI_NEXT_CONSOLE_MESSAGE 252 
#define  BOTLIB_AI_NUM_CONSOLE_MESSAGE 251 
#define  BOTLIB_AI_NUM_INITIAL_CHATS 250 
#define  BOTLIB_AI_POP_GOAL 249 
#define  BOTLIB_AI_PREDICT_VISIBLE_POSITION 248 
#define  BOTLIB_AI_PUSH_GOAL 247 
#define  BOTLIB_AI_QUEUE_CONSOLE_MESSAGE 246 
#define  BOTLIB_AI_REACHABILITY_AREA 245 
#define  BOTLIB_AI_REMOVE_CONSOLE_MESSAGE 244 
#define  BOTLIB_AI_REMOVE_FROM_AVOID_GOALS 243 
#define  BOTLIB_AI_REPLACE_SYNONYMS 242 
#define  BOTLIB_AI_REPLY_CHAT 241 
#define  BOTLIB_AI_RESET_AVOID_GOALS 240 
#define  BOTLIB_AI_RESET_AVOID_REACH 239 
#define  BOTLIB_AI_RESET_GOAL_STATE 238 
#define  BOTLIB_AI_RESET_LAST_AVOID_REACH 237 
#define  BOTLIB_AI_RESET_MOVE_STATE 236 
#define  BOTLIB_AI_RESET_WEAPON_STATE 235 
#define  BOTLIB_AI_SAVE_GOAL_FUZZY_LOGIC 234 
#define  BOTLIB_AI_SET_AVOID_GOAL_TIME 233 
#define  BOTLIB_AI_SET_CHAT_GENDER 232 
#define  BOTLIB_AI_SET_CHAT_NAME 231 
#define  BOTLIB_AI_STRING_CONTAINS 230 
#define  BOTLIB_AI_TOUCHING_GOAL 229 
#define  BOTLIB_AI_UNIFY_WHITE_SPACES 228 
#define  BOTLIB_AI_UPDATE_ENTITY_ITEMS 227 
#define  BOTLIB_EA_ACTION 226 
#define  BOTLIB_EA_ATTACK 225 
#define  BOTLIB_EA_COMMAND 224 
#define  BOTLIB_EA_CROUCH 223 
#define  BOTLIB_EA_DELAYED_JUMP 222 
#define  BOTLIB_EA_END_REGULAR 221 
#define  BOTLIB_EA_GESTURE 220 
#define  BOTLIB_EA_GET_INPUT 219 
#define  BOTLIB_EA_JUMP 218 
#define  BOTLIB_EA_MOVE 217 
#define  BOTLIB_EA_MOVE_BACK 216 
#define  BOTLIB_EA_MOVE_DOWN 215 
#define  BOTLIB_EA_MOVE_FORWARD 214 
#define  BOTLIB_EA_MOVE_LEFT 213 
#define  BOTLIB_EA_MOVE_RIGHT 212 
#define  BOTLIB_EA_MOVE_UP 211 
#define  BOTLIB_EA_RESET_INPUT 210 
#define  BOTLIB_EA_RESPAWN 209 
#define  BOTLIB_EA_SAY 208 
#define  BOTLIB_EA_SAY_TEAM 207 
#define  BOTLIB_EA_SELECT_WEAPON 206 
#define  BOTLIB_EA_TALK 205 
#define  BOTLIB_EA_USE 204 
#define  BOTLIB_EA_VIEW 203 
#define  BOTLIB_GET_CONSOLE_MESSAGE 202 
#define  BOTLIB_GET_SNAPSHOT_ENTITY 201 
#define  BOTLIB_LIBVAR_GET 200 
#define  BOTLIB_LIBVAR_SET 199 
#define  BOTLIB_LOAD_MAP 198 
#define  BOTLIB_PC_ADD_GLOBAL_DEFINE 197 
#define  BOTLIB_PC_FREE_SOURCE 196 
#define  BOTLIB_PC_LOAD_SOURCE 195 
#define  BOTLIB_PC_READ_TOKEN 194 
#define  BOTLIB_PC_SOURCE_FILE_AND_LINE 193 
#define  BOTLIB_SETUP 192 
#define  BOTLIB_SHUTDOWN 191 
#define  BOTLIB_START_FRAME 190 
#define  BOTLIB_TEST 189 
#define  BOTLIB_UPDATENTITY 188 
#define  BOTLIB_USER_COMMAND 187 
 intptr_t BotImport_DebugPolygonCreate (intptr_t,intptr_t,scalar_t__) ; 
 int /*<<< orphan*/  BotImport_DebugPolygonDelete (intptr_t) ; 
 intptr_t CM_AreasConnected (intptr_t,intptr_t) ; 
 char* COM_Parse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Cbuf_ExecuteText (intptr_t,scalar_t__) ; 
 intptr_t Cmd_Argc () ; 
 int /*<<< orphan*/  Cmd_ArgvBuffer (intptr_t,scalar_t__,intptr_t) ; 
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  Com_Memcpy (scalar_t__,scalar_t__,intptr_t) ; 
 int /*<<< orphan*/  Com_Memset (scalar_t__,intptr_t,intptr_t) ; 
 int /*<<< orphan*/  Com_Printf (char*,char const*) ; 
 intptr_t Com_RealTime (scalar_t__) ; 
 int /*<<< orphan*/  Cvar_Register (scalar_t__,scalar_t__,scalar_t__,intptr_t) ; 
 int /*<<< orphan*/  Cvar_SetSafe (char const*,char const*) ; 
 int /*<<< orphan*/  Cvar_Update (scalar_t__) ; 
 intptr_t Cvar_VariableIntegerValue (char const*) ; 
 int /*<<< orphan*/  Cvar_VariableStringBuffer (scalar_t__,scalar_t__,intptr_t) ; 
 int /*<<< orphan*/  ERR_DROP ; 
 int /*<<< orphan*/  FS_FCloseFile (intptr_t) ; 
 intptr_t FS_FOpenFileByMode (scalar_t__,scalar_t__,intptr_t) ; 
 intptr_t FS_GetFileList (scalar_t__,scalar_t__,scalar_t__,intptr_t) ; 
 int /*<<< orphan*/  FS_Read (scalar_t__,intptr_t,intptr_t) ; 
 intptr_t FS_Seek (intptr_t,intptr_t,intptr_t) ; 
 int /*<<< orphan*/  FS_Write (scalar_t__,intptr_t,intptr_t) ; 
 intptr_t FloatAsInt (int /*<<< orphan*/ ) ; 
#define  G_ADJUST_AREA_PORTAL_STATE 186 
#define  G_AREAS_CONNECTED 185 
#define  G_ARGC 184 
#define  G_ARGV 183 
#define  G_BOT_ALLOCATE_CLIENT 182 
#define  G_BOT_FREE_CLIENT 181 
#define  G_CVAR_REGISTER 180 
#define  G_CVAR_SET 179 
#define  G_CVAR_UPDATE 178 
#define  G_CVAR_VARIABLE_INTEGER_VALUE 177 
#define  G_CVAR_VARIABLE_STRING_BUFFER 176 
#define  G_DEBUG_POLYGON_CREATE 175 
#define  G_DEBUG_POLYGON_DELETE 174 
#define  G_DEEPMIND_CALLBACK 173 
#define  G_DROP_CLIENT 172 
#define  G_ENTITIES_IN_BOX 171 
#define  G_ENTITY_CONTACT 170 
#define  G_ENTITY_CONTACTCAPSULE 169 
#define  G_ERROR 168 
#define  G_FS_FCLOSE_FILE 167 
#define  G_FS_FOPEN_FILE 166 
#define  G_FS_GETFILELIST 165 
#define  G_FS_READ 164 
#define  G_FS_SEEK 163 
#define  G_FS_WRITE 162 
#define  G_GET_CONFIGSTRING 161 
#define  G_GET_ENTITY_TOKEN 160 
#define  G_GET_SERVERINFO 159 
#define  G_GET_USERCMD 158 
#define  G_GET_USERINFO 157 
#define  G_IN_PVS 156 
#define  G_IN_PVS_IGNORE_PORTALS 155 
#define  G_LINKENTITY 154 
#define  G_LOCATE_GAME_DATA 153 
#define  G_MILLISECONDS 152 
#define  G_POINT_CONTENTS 151 
#define  G_PRINT 150 
#define  G_REAL_TIME 149 
#define  G_SEND_CONSOLE_COMMAND 148 
#define  G_SEND_SERVER_COMMAND 147 
#define  G_SET_BRUSH_MODEL 146 
#define  G_SET_CONFIGSTRING 145 
#define  G_SET_USERINFO 144 
#define  G_SNAPVECTOR 143 
#define  G_TRACE 142 
#define  G_TRACECAPSULE 141 
#define  G_UNLINKENTITY 140 
 int /*<<< orphan*/  MatrixMultiply (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PerpendicularVector (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  Q_SnapVector (scalar_t__) ; 
 int /*<<< orphan*/  Q_strncpyz (scalar_t__,char const*,intptr_t) ; 
 int /*<<< orphan*/  SV_AdjustAreaPortalState (scalar_t__,intptr_t) ; 
 intptr_t SV_AreaEntities (scalar_t__,scalar_t__,scalar_t__,intptr_t) ; 
 intptr_t SV_BotAllocateClient () ; 
 int /*<<< orphan*/  SV_BotFreeClient (intptr_t) ; 
 intptr_t SV_BotGetConsoleMessage (intptr_t,scalar_t__,intptr_t) ; 
 intptr_t SV_BotGetSnapshotEntity (intptr_t,intptr_t) ; 
 intptr_t SV_BotLibSetup () ; 
 intptr_t SV_BotLibShutdown () ; 
 int /*<<< orphan*/  SV_ClientThink (int /*<<< orphan*/ *,scalar_t__) ; 
 intptr_t SV_EntityContact (scalar_t__,scalar_t__,scalar_t__,intptr_t) ; 
 int /*<<< orphan*/  SV_GameDropClient (intptr_t,scalar_t__) ; 
 int /*<<< orphan*/  SV_GameSendServerCommand (intptr_t,scalar_t__) ; 
 int /*<<< orphan*/  SV_GetConfigstring (intptr_t,scalar_t__,intptr_t) ; 
 int /*<<< orphan*/  SV_GetServerinfo (scalar_t__,intptr_t) ; 
 int /*<<< orphan*/  SV_GetUsercmd (intptr_t,scalar_t__) ; 
 int /*<<< orphan*/  SV_GetUserinfo (intptr_t,scalar_t__,intptr_t) ; 
 int /*<<< orphan*/  SV_LinkEntity (scalar_t__) ; 
 int /*<<< orphan*/  SV_LocateGameData (scalar_t__,intptr_t,intptr_t,scalar_t__,intptr_t) ; 
 intptr_t SV_PointContents (scalar_t__,intptr_t) ; 
 int /*<<< orphan*/  SV_SetBrushModel (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SV_SetConfigstring (intptr_t,scalar_t__) ; 
 int /*<<< orphan*/  SV_SetUserinfo (intptr_t,scalar_t__) ; 
 int /*<<< orphan*/  SV_Trace (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,intptr_t,intptr_t,intptr_t) ; 
 int /*<<< orphan*/  SV_UnlinkEntity (scalar_t__) ; 
 intptr_t SV_inPVS (scalar_t__,scalar_t__) ; 
 intptr_t SV_inPVSIgnorePortals (scalar_t__,scalar_t__) ; 
 intptr_t Sys_Milliseconds () ; 
#define  TRAP_ANGLEVECTORS 139 
#define  TRAP_ATAN2 138 
#define  TRAP_CEIL 137 
#define  TRAP_COS 136 
#define  TRAP_FLOOR 135 
#define  TRAP_MATRIXMULTIPLY 134 
#define  TRAP_MEMCPY 133 
#define  TRAP_MEMSET 132 
#define  TRAP_PERPENDICULARVECTOR 131 
#define  TRAP_SIN 130 
#define  TRAP_SQRT 129 
#define  TRAP_STRNCPY 128 
 scalar_t__ VMA (int) ; 
 int /*<<< orphan*/  VMF (int) ; 
 int /*<<< orphan*/  atan2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__* botlib_export ; 
 int /*<<< orphan*/  ceil (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cos (int /*<<< orphan*/ ) ; 
 intptr_t dmlab_callback (intptr_t,intptr_t,intptr_t,intptr_t,intptr_t,intptr_t,intptr_t,intptr_t,intptr_t,intptr_t,intptr_t,intptr_t,intptr_t) ; 
 int /*<<< orphan*/  floor (int /*<<< orphan*/ ) ; 
 intptr_t qfalse ; 
 intptr_t qtrue ; 
 int /*<<< orphan*/  sin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqrt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (scalar_t__,scalar_t__,intptr_t) ; 
 intptr_t stub1 (scalar_t__,scalar_t__) ; 
 intptr_t stub10 (intptr_t,scalar_t__) ; 
 intptr_t stub100 (intptr_t,scalar_t__,scalar_t__) ; 
 intptr_t stub101 (intptr_t,scalar_t__) ; 
 intptr_t stub102 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub103 (intptr_t,intptr_t) ; 
 int /*<<< orphan*/  stub104 (intptr_t,intptr_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub105 () ; 
 int /*<<< orphan*/  stub106 () ; 
 intptr_t stub107 (intptr_t,scalar_t__) ; 
 int /*<<< orphan*/  stub108 (intptr_t) ; 
 int /*<<< orphan*/  stub109 (intptr_t,intptr_t,intptr_t) ; 
 intptr_t stub11 (intptr_t,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub110 (intptr_t,scalar_t__) ; 
 int /*<<< orphan*/  stub111 (intptr_t,int /*<<< orphan*/ ) ; 
 intptr_t stub112 (intptr_t) ; 
 int /*<<< orphan*/  stub113 (intptr_t) ; 
 int /*<<< orphan*/  stub114 (intptr_t) ; 
 int /*<<< orphan*/  stub115 (intptr_t,scalar_t__,int /*<<< orphan*/ ,intptr_t) ; 
 int /*<<< orphan*/  stub116 (scalar_t__,intptr_t,scalar_t__,intptr_t) ; 
 intptr_t stub117 (intptr_t,scalar_t__,int /*<<< orphan*/ ,intptr_t) ; 
 int /*<<< orphan*/  stub118 (intptr_t) ; 
 int /*<<< orphan*/  stub119 (intptr_t) ; 
 intptr_t stub12 (scalar_t__,scalar_t__,scalar_t__,intptr_t) ; 
 intptr_t stub120 (scalar_t__,intptr_t) ; 
 intptr_t stub121 (intptr_t,scalar_t__,intptr_t,int /*<<< orphan*/ ,scalar_t__) ; 
 intptr_t stub122 (scalar_t__,intptr_t,scalar_t__,intptr_t,scalar_t__) ; 
 intptr_t stub123 () ; 
 int /*<<< orphan*/  stub124 (intptr_t) ; 
 int /*<<< orphan*/  stub125 (intptr_t,scalar_t__) ; 
 intptr_t stub126 (intptr_t,scalar_t__) ; 
 int /*<<< orphan*/  stub127 (intptr_t,intptr_t,scalar_t__) ; 
 intptr_t stub128 (intptr_t,scalar_t__) ; 
 intptr_t stub129 () ; 
 intptr_t stub13 (intptr_t,scalar_t__) ; 
 int /*<<< orphan*/  stub130 (intptr_t) ; 
 int /*<<< orphan*/  stub131 (intptr_t) ; 
 intptr_t stub132 (intptr_t,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 intptr_t stub14 (scalar_t__,intptr_t,scalar_t__,intptr_t,intptr_t,scalar_t__,intptr_t,intptr_t) ; 
 int /*<<< orphan*/  stub15 (intptr_t,scalar_t__) ; 
 intptr_t stub16 () ; 
 int /*<<< orphan*/  stub17 (intptr_t,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub18 () ; 
 intptr_t stub19 (scalar_t__) ; 
 intptr_t stub2 (scalar_t__,scalar_t__,intptr_t) ; 
 intptr_t stub20 (scalar_t__) ; 
 intptr_t stub21 (scalar_t__,scalar_t__,scalar_t__,scalar_t__,intptr_t) ; 
 intptr_t stub22 (scalar_t__) ; 
 intptr_t stub23 (intptr_t) ; 
 intptr_t stub24 (intptr_t,scalar_t__,scalar_t__,intptr_t) ; 
 intptr_t stub25 (intptr_t,scalar_t__,scalar_t__) ; 
 intptr_t stub26 (intptr_t,scalar_t__,scalar_t__) ; 
 intptr_t stub27 (intptr_t,scalar_t__,scalar_t__) ; 
 intptr_t stub28 (intptr_t) ; 
 intptr_t stub29 (intptr_t,scalar_t__,intptr_t,intptr_t) ; 
 intptr_t stub3 (scalar_t__) ; 
 intptr_t stub30 (intptr_t,intptr_t) ; 
 intptr_t stub31 (scalar_t__,intptr_t,scalar_t__,intptr_t,intptr_t,intptr_t,intptr_t,intptr_t,intptr_t,intptr_t,intptr_t) ; 
 intptr_t stub32 (scalar_t__) ; 
 intptr_t stub33 (scalar_t__,intptr_t,scalar_t__,intptr_t,intptr_t,scalar_t__,scalar_t__,intptr_t,intptr_t,int /*<<< orphan*/ ,intptr_t,intptr_t,intptr_t) ; 
 int /*<<< orphan*/  stub34 (intptr_t,scalar_t__) ; 
 int /*<<< orphan*/  stub35 (intptr_t,scalar_t__) ; 
 int /*<<< orphan*/  stub36 (intptr_t,scalar_t__) ; 
 int /*<<< orphan*/  stub37 (intptr_t,intptr_t) ; 
 int /*<<< orphan*/  stub38 (intptr_t) ; 
 int /*<<< orphan*/  stub39 (intptr_t) ; 
 intptr_t stub4 (scalar_t__) ; 
 int /*<<< orphan*/  stub40 (intptr_t) ; 
 int /*<<< orphan*/  stub41 (intptr_t) ; 
 int /*<<< orphan*/  stub42 (intptr_t) ; 
 int /*<<< orphan*/  stub43 (intptr_t) ; 
 int /*<<< orphan*/  stub44 (intptr_t) ; 
 int /*<<< orphan*/  stub45 (intptr_t) ; 
 int /*<<< orphan*/  stub46 (intptr_t) ; 
 int /*<<< orphan*/  stub47 (intptr_t) ; 
 int /*<<< orphan*/  stub48 (intptr_t) ; 
 int /*<<< orphan*/  stub49 (intptr_t) ; 
 intptr_t stub5 (intptr_t) ; 
 int /*<<< orphan*/  stub50 (intptr_t,intptr_t) ; 
 int /*<<< orphan*/  stub51 (intptr_t) ; 
 int /*<<< orphan*/  stub52 (intptr_t) ; 
 int /*<<< orphan*/  stub53 (intptr_t,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub54 (intptr_t,scalar_t__) ; 
 int /*<<< orphan*/  stub55 (intptr_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub56 (intptr_t,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub57 (intptr_t) ; 
 intptr_t stub58 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub59 (intptr_t) ; 
 intptr_t stub6 (intptr_t,scalar_t__) ; 
 int /*<<< orphan*/  stub60 (intptr_t,intptr_t) ; 
 int /*<<< orphan*/  stub61 (intptr_t,intptr_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 intptr_t stub62 (intptr_t,intptr_t) ; 
 intptr_t stub63 (intptr_t,intptr_t,intptr_t,intptr_t) ; 
 int /*<<< orphan*/  stub64 (intptr_t,intptr_t,scalar_t__,intptr_t) ; 
 intptr_t stub65 () ; 
 int /*<<< orphan*/  stub66 (intptr_t) ; 
 int /*<<< orphan*/  stub67 (intptr_t,intptr_t,scalar_t__) ; 
 int /*<<< orphan*/  stub68 (intptr_t,intptr_t) ; 
 intptr_t stub69 (intptr_t,scalar_t__) ; 
 intptr_t stub7 (intptr_t,scalar_t__,scalar_t__) ; 
 intptr_t stub70 (intptr_t) ; 
 int /*<<< orphan*/  stub71 (intptr_t,scalar_t__,intptr_t,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 intptr_t stub72 (intptr_t,scalar_t__) ; 
 intptr_t stub73 (intptr_t,scalar_t__,intptr_t,intptr_t,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 intptr_t stub74 (intptr_t) ; 
 int /*<<< orphan*/  stub75 (intptr_t,intptr_t,intptr_t) ; 
 int /*<<< orphan*/  stub76 (intptr_t,scalar_t__,intptr_t) ; 
 intptr_t stub77 (scalar_t__,scalar_t__,intptr_t) ; 
 intptr_t stub78 (scalar_t__,scalar_t__,intptr_t) ; 
 int /*<<< orphan*/  stub79 (scalar_t__,intptr_t,scalar_t__,intptr_t) ; 
 intptr_t stub8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub80 (scalar_t__) ; 
 int /*<<< orphan*/  stub81 (scalar_t__,intptr_t) ; 
 intptr_t stub82 (intptr_t,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub83 (intptr_t,intptr_t) ; 
 int /*<<< orphan*/  stub84 (intptr_t,scalar_t__,intptr_t) ; 
 int /*<<< orphan*/  stub85 (intptr_t) ; 
 int /*<<< orphan*/  stub86 (intptr_t) ; 
 int /*<<< orphan*/  stub87 (intptr_t,intptr_t) ; 
 int /*<<< orphan*/  stub88 (intptr_t,scalar_t__) ; 
 int /*<<< orphan*/  stub89 (intptr_t) ; 
 intptr_t stub9 (scalar_t__) ; 
 int /*<<< orphan*/  stub90 (intptr_t) ; 
 int /*<<< orphan*/  stub91 (intptr_t) ; 
 int /*<<< orphan*/  stub92 (intptr_t) ; 
 int /*<<< orphan*/  stub93 (intptr_t,scalar_t__,intptr_t) ; 
 intptr_t stub94 (intptr_t,scalar_t__) ; 
 intptr_t stub95 (intptr_t,scalar_t__) ; 
 intptr_t stub96 (intptr_t,scalar_t__,scalar_t__,intptr_t) ; 
 intptr_t stub97 (intptr_t,scalar_t__,scalar_t__,intptr_t,scalar_t__,int /*<<< orphan*/ ) ; 
 intptr_t stub98 (scalar_t__,scalar_t__) ; 
 intptr_t stub99 (intptr_t,scalar_t__,scalar_t__,scalar_t__) ; 
 TYPE_6__ sv ; 
 TYPE_5__* sv_maxclients ; 
 TYPE_4__ svs ; 

intptr_t SV_GameSystemCalls( intptr_t *args ) {
	switch( args[0] ) {
	case G_PRINT:
		Com_Printf( "%s", (const char*)VMA(1) );
		return 0;
	case G_ERROR:
		Com_Error( ERR_DROP, "%s", (const char*)VMA(1) );
		return 0;
	case G_MILLISECONDS:
		return Sys_Milliseconds();
	case G_CVAR_REGISTER:
		Cvar_Register( VMA(1), VMA(2), VMA(3), args[4] ); 
		return 0;
	case G_CVAR_UPDATE:
		Cvar_Update( VMA(1) );
		return 0;
	case G_CVAR_SET:
		Cvar_SetSafe( (const char *)VMA(1), (const char *)VMA(2) );
		return 0;
	case G_CVAR_VARIABLE_INTEGER_VALUE:
		return Cvar_VariableIntegerValue( (const char *)VMA(1) );
	case G_CVAR_VARIABLE_STRING_BUFFER:
		Cvar_VariableStringBuffer( VMA(1), VMA(2), args[3] );
		return 0;
	case G_ARGC:
		return Cmd_Argc();
	case G_ARGV:
		Cmd_ArgvBuffer( args[1], VMA(2), args[3] );
		return 0;
	case G_SEND_CONSOLE_COMMAND:
		Cbuf_ExecuteText( args[1], VMA(2) );
		return 0;

	case G_FS_FOPEN_FILE:
		return FS_FOpenFileByMode( VMA(1), VMA(2), args[3] );
	case G_FS_READ:
		FS_Read( VMA(1), args[2], args[3] );
		return 0;
	case G_FS_WRITE:
		FS_Write( VMA(1), args[2], args[3] );
		return 0;
	case G_FS_FCLOSE_FILE:
		FS_FCloseFile( args[1] );
		return 0;
	case G_FS_GETFILELIST:
		return FS_GetFileList( VMA(1), VMA(2), VMA(3), args[4] );
	case G_FS_SEEK:
		return FS_Seek( args[1], args[2], args[3] );

	case G_LOCATE_GAME_DATA:
		SV_LocateGameData( VMA(1), args[2], args[3], VMA(4), args[5] );
		return 0;
	case G_DROP_CLIENT:
		SV_GameDropClient( args[1], VMA(2) );
		return 0;
	case G_SEND_SERVER_COMMAND:
		SV_GameSendServerCommand( args[1], VMA(2) );
		return 0;
	case G_LINKENTITY:
		SV_LinkEntity( VMA(1) );
		return 0;
	case G_UNLINKENTITY:
		SV_UnlinkEntity( VMA(1) );
		return 0;
	case G_ENTITIES_IN_BOX:
		return SV_AreaEntities( VMA(1), VMA(2), VMA(3), args[4] );
	case G_ENTITY_CONTACT:
		return SV_EntityContact( VMA(1), VMA(2), VMA(3), /*int capsule*/ qfalse );
	case G_ENTITY_CONTACTCAPSULE:
		return SV_EntityContact( VMA(1), VMA(2), VMA(3), /*int capsule*/ qtrue );
	case G_TRACE:
		SV_Trace( VMA(1), VMA(2), VMA(3), VMA(4), VMA(5), args[6], args[7], /*int capsule*/ qfalse );
		return 0;
	case G_TRACECAPSULE:
		SV_Trace( VMA(1), VMA(2), VMA(3), VMA(4), VMA(5), args[6], args[7], /*int capsule*/ qtrue );
		return 0;
	case G_POINT_CONTENTS:
		return SV_PointContents( VMA(1), args[2] );
	case G_SET_BRUSH_MODEL:
		SV_SetBrushModel( VMA(1), VMA(2) );
		return 0;
	case G_IN_PVS:
		return SV_inPVS( VMA(1), VMA(2) );
	case G_IN_PVS_IGNORE_PORTALS:
		return SV_inPVSIgnorePortals( VMA(1), VMA(2) );

	case G_SET_CONFIGSTRING:
		SV_SetConfigstring( args[1], VMA(2) );
		return 0;
	case G_GET_CONFIGSTRING:
		SV_GetConfigstring( args[1], VMA(2), args[3] );
		return 0;
	case G_SET_USERINFO:
		SV_SetUserinfo( args[1], VMA(2) );
		return 0;
	case G_GET_USERINFO:
		SV_GetUserinfo( args[1], VMA(2), args[3] );
		return 0;
	case G_GET_SERVERINFO:
		SV_GetServerinfo( VMA(1), args[2] );
		return 0;
	case G_ADJUST_AREA_PORTAL_STATE:
		SV_AdjustAreaPortalState( VMA(1), args[2] );
		return 0;
	case G_AREAS_CONNECTED:
		return CM_AreasConnected( args[1], args[2] );

	case G_BOT_ALLOCATE_CLIENT:
		return SV_BotAllocateClient();
	case G_BOT_FREE_CLIENT:
		SV_BotFreeClient( args[1] );
		return 0;

	case G_GET_USERCMD:
		SV_GetUsercmd( args[1], VMA(2) );
		return 0;
	case G_GET_ENTITY_TOKEN:
		{
			const char	*s;

			s = COM_Parse( &sv.entityParsePoint );
			Q_strncpyz( VMA(1), s, args[2] );
			if ( !sv.entityParsePoint && !s[0] ) {
				return qfalse;
			} else {
				return qtrue;
			}
		}

	case G_DEBUG_POLYGON_CREATE:
		return BotImport_DebugPolygonCreate( args[1], args[2], VMA(3) );
	case G_DEBUG_POLYGON_DELETE:
		BotImport_DebugPolygonDelete( args[1] );
		return 0;
	case G_REAL_TIME:
		return Com_RealTime( VMA(1) );
	case G_SNAPVECTOR:
		Q_SnapVector(VMA(1));
		return 0;

		//====================================

	case BOTLIB_SETUP:
		return SV_BotLibSetup();
	case BOTLIB_SHUTDOWN:
		return SV_BotLibShutdown();
	case BOTLIB_LIBVAR_SET:
		return botlib_export->BotLibVarSet( VMA(1), VMA(2) );
	case BOTLIB_LIBVAR_GET:
		return botlib_export->BotLibVarGet( VMA(1), VMA(2), args[3] );

	case BOTLIB_PC_ADD_GLOBAL_DEFINE:
		return botlib_export->PC_AddGlobalDefine( VMA(1) );
	case BOTLIB_PC_LOAD_SOURCE:
		return botlib_export->PC_LoadSourceHandle( VMA(1) );
	case BOTLIB_PC_FREE_SOURCE:
		return botlib_export->PC_FreeSourceHandle( args[1] );
	case BOTLIB_PC_READ_TOKEN:
		return botlib_export->PC_ReadTokenHandle( args[1], VMA(2) );
	case BOTLIB_PC_SOURCE_FILE_AND_LINE:
		return botlib_export->PC_SourceFileAndLine( args[1], VMA(2), VMA(3) );

	case BOTLIB_START_FRAME:
		return botlib_export->BotLibStartFrame( VMF(1) );
	case BOTLIB_LOAD_MAP:
		return botlib_export->BotLibLoadMap( VMA(1) );
	case BOTLIB_UPDATENTITY:
		return botlib_export->BotLibUpdateEntity( args[1], VMA(2) );
	case BOTLIB_TEST:
		return botlib_export->Test( args[1], VMA(2), VMA(3), VMA(4) );

	case BOTLIB_GET_SNAPSHOT_ENTITY:
		return SV_BotGetSnapshotEntity( args[1], args[2] );
	case BOTLIB_GET_CONSOLE_MESSAGE:
		return SV_BotGetConsoleMessage( args[1], VMA(2), args[3] );
	case BOTLIB_USER_COMMAND:
		{
			int clientNum = args[1];

			if ( clientNum >= 0 && clientNum < sv_maxclients->integer ) {
				SV_ClientThink( &svs.clients[clientNum], VMA(2) );
			}
		}
		return 0;

	case BOTLIB_AAS_BBOX_AREAS:
		return botlib_export->aas.AAS_BBoxAreas( VMA(1), VMA(2), VMA(3), args[4] );
	case BOTLIB_AAS_AREA_INFO:
		return botlib_export->aas.AAS_AreaInfo( args[1], VMA(2) );
	case BOTLIB_AAS_ALTERNATIVE_ROUTE_GOAL:
		return botlib_export->aas.AAS_AlternativeRouteGoals( VMA(1), args[2], VMA(3), args[4], args[5], VMA(6), args[7], args[8] );
	case BOTLIB_AAS_ENTITY_INFO:
		botlib_export->aas.AAS_EntityInfo( args[1], VMA(2) );
		return 0;

	case BOTLIB_AAS_INITIALIZED:
		return botlib_export->aas.AAS_Initialized();
	case BOTLIB_AAS_PRESENCE_TYPE_BOUNDING_BOX:
		botlib_export->aas.AAS_PresenceTypeBoundingBox( args[1], VMA(2), VMA(3) );
		return 0;
	case BOTLIB_AAS_TIME:
		return FloatAsInt( botlib_export->aas.AAS_Time() );

	case BOTLIB_AAS_POINT_AREA_NUM:
		return botlib_export->aas.AAS_PointAreaNum( VMA(1) );
	case BOTLIB_AAS_POINT_REACHABILITY_AREA_INDEX:
		return botlib_export->aas.AAS_PointReachabilityAreaIndex( VMA(1) );
	case BOTLIB_AAS_TRACE_AREAS:
		return botlib_export->aas.AAS_TraceAreas( VMA(1), VMA(2), VMA(3), VMA(4), args[5] );

	case BOTLIB_AAS_POINT_CONTENTS:
		return botlib_export->aas.AAS_PointContents( VMA(1) );
	case BOTLIB_AAS_NEXT_BSP_ENTITY:
		return botlib_export->aas.AAS_NextBSPEntity( args[1] );
	case BOTLIB_AAS_VALUE_FOR_BSP_EPAIR_KEY:
		return botlib_export->aas.AAS_ValueForBSPEpairKey( args[1], VMA(2), VMA(3), args[4] );
	case BOTLIB_AAS_VECTOR_FOR_BSP_EPAIR_KEY:
		return botlib_export->aas.AAS_VectorForBSPEpairKey( args[1], VMA(2), VMA(3) );
	case BOTLIB_AAS_FLOAT_FOR_BSP_EPAIR_KEY:
		return botlib_export->aas.AAS_FloatForBSPEpairKey( args[1], VMA(2), VMA(3) );
	case BOTLIB_AAS_INT_FOR_BSP_EPAIR_KEY:
		return botlib_export->aas.AAS_IntForBSPEpairKey( args[1], VMA(2), VMA(3) );

	case BOTLIB_AAS_AREA_REACHABILITY:
		return botlib_export->aas.AAS_AreaReachability( args[1] );

	case BOTLIB_AAS_AREA_TRAVEL_TIME_TO_GOAL_AREA:
		return botlib_export->aas.AAS_AreaTravelTimeToGoalArea( args[1], VMA(2), args[3], args[4] );
	case BOTLIB_AAS_ENABLE_ROUTING_AREA:
		return botlib_export->aas.AAS_EnableRoutingArea( args[1], args[2] );
	case BOTLIB_AAS_PREDICT_ROUTE:
		return botlib_export->aas.AAS_PredictRoute( VMA(1), args[2], VMA(3), args[4], args[5], args[6], args[7], args[8], args[9], args[10], args[11] );

	case BOTLIB_AAS_SWIMMING:
		return botlib_export->aas.AAS_Swimming( VMA(1) );
	case BOTLIB_AAS_PREDICT_CLIENT_MOVEMENT:
		return botlib_export->aas.AAS_PredictClientMovement( VMA(1), args[2], VMA(3), args[4], args[5],
			VMA(6), VMA(7), args[8], args[9], VMF(10), args[11], args[12], args[13] );

	case BOTLIB_EA_SAY:
		botlib_export->ea.EA_Say( args[1], VMA(2) );
		return 0;
	case BOTLIB_EA_SAY_TEAM:
		botlib_export->ea.EA_SayTeam( args[1], VMA(2) );
		return 0;
	case BOTLIB_EA_COMMAND:
		botlib_export->ea.EA_Command( args[1], VMA(2) );
		return 0;

	case BOTLIB_EA_ACTION:
		botlib_export->ea.EA_Action( args[1], args[2] );
		return 0;
	case BOTLIB_EA_GESTURE:
		botlib_export->ea.EA_Gesture( args[1] );
		return 0;
	case BOTLIB_EA_TALK:
		botlib_export->ea.EA_Talk( args[1] );
		return 0;
	case BOTLIB_EA_ATTACK:
		botlib_export->ea.EA_Attack( args[1] );
		return 0;
	case BOTLIB_EA_USE:
		botlib_export->ea.EA_Use( args[1] );
		return 0;
	case BOTLIB_EA_RESPAWN:
		botlib_export->ea.EA_Respawn( args[1] );
		return 0;
	case BOTLIB_EA_CROUCH:
		botlib_export->ea.EA_Crouch( args[1] );
		return 0;
	case BOTLIB_EA_MOVE_UP:
		botlib_export->ea.EA_MoveUp( args[1] );
		return 0;
	case BOTLIB_EA_MOVE_DOWN:
		botlib_export->ea.EA_MoveDown( args[1] );
		return 0;
	case BOTLIB_EA_MOVE_FORWARD:
		botlib_export->ea.EA_MoveForward( args[1] );
		return 0;
	case BOTLIB_EA_MOVE_BACK:
		botlib_export->ea.EA_MoveBack( args[1] );
		return 0;
	case BOTLIB_EA_MOVE_LEFT:
		botlib_export->ea.EA_MoveLeft( args[1] );
		return 0;
	case BOTLIB_EA_MOVE_RIGHT:
		botlib_export->ea.EA_MoveRight( args[1] );
		return 0;

	case BOTLIB_EA_SELECT_WEAPON:
		botlib_export->ea.EA_SelectWeapon( args[1], args[2] );
		return 0;
	case BOTLIB_EA_JUMP:
		botlib_export->ea.EA_Jump( args[1] );
		return 0;
	case BOTLIB_EA_DELAYED_JUMP:
		botlib_export->ea.EA_DelayedJump( args[1] );
		return 0;
	case BOTLIB_EA_MOVE:
		botlib_export->ea.EA_Move( args[1], VMA(2), VMF(3) );
		return 0;
	case BOTLIB_EA_VIEW:
		botlib_export->ea.EA_View( args[1], VMA(2) );
		return 0;

	case BOTLIB_EA_END_REGULAR:
		botlib_export->ea.EA_EndRegular( args[1], VMF(2) );
		return 0;
	case BOTLIB_EA_GET_INPUT:
		botlib_export->ea.EA_GetInput( args[1], VMF(2), VMA(3) );
		return 0;
	case BOTLIB_EA_RESET_INPUT:
		botlib_export->ea.EA_ResetInput( args[1] );
		return 0;

	case BOTLIB_AI_LOAD_CHARACTER:
		return botlib_export->ai.BotLoadCharacter( VMA(1), VMF(2) );
	case BOTLIB_AI_FREE_CHARACTER:
		botlib_export->ai.BotFreeCharacter( args[1] );
		return 0;
	case BOTLIB_AI_CHARACTERISTIC_FLOAT:
		return FloatAsInt( botlib_export->ai.Characteristic_Float( args[1], args[2] ) );
	case BOTLIB_AI_CHARACTERISTIC_BFLOAT:
		return FloatAsInt( botlib_export->ai.Characteristic_BFloat( args[1], args[2], VMF(3), VMF(4) ) );
	case BOTLIB_AI_CHARACTERISTIC_INTEGER:
		return botlib_export->ai.Characteristic_Integer( args[1], args[2] );
	case BOTLIB_AI_CHARACTERISTIC_BINTEGER:
		return botlib_export->ai.Characteristic_BInteger( args[1], args[2], args[3], args[4] );
	case BOTLIB_AI_CHARACTERISTIC_STRING:
		botlib_export->ai.Characteristic_String( args[1], args[2], VMA(3), args[4] );
		return 0;

	case BOTLIB_AI_ALLOC_CHAT_STATE:
		return botlib_export->ai.BotAllocChatState();
	case BOTLIB_AI_FREE_CHAT_STATE:
		botlib_export->ai.BotFreeChatState( args[1] );
		return 0;
	case BOTLIB_AI_QUEUE_CONSOLE_MESSAGE:
		botlib_export->ai.BotQueueConsoleMessage( args[1], args[2], VMA(3) );
		return 0;
	case BOTLIB_AI_REMOVE_CONSOLE_MESSAGE:
		botlib_export->ai.BotRemoveConsoleMessage( args[1], args[2] );
		return 0;
	case BOTLIB_AI_NEXT_CONSOLE_MESSAGE:
		return botlib_export->ai.BotNextConsoleMessage( args[1], VMA(2) );
	case BOTLIB_AI_NUM_CONSOLE_MESSAGE:
		return botlib_export->ai.BotNumConsoleMessages( args[1] );
	case BOTLIB_AI_INITIAL_CHAT:
		botlib_export->ai.BotInitialChat( args[1], VMA(2), args[3], VMA(4), VMA(5), VMA(6), VMA(7), VMA(8), VMA(9), VMA(10), VMA(11) );
		return 0;
	case BOTLIB_AI_NUM_INITIAL_CHATS:
		return botlib_export->ai.BotNumInitialChats( args[1], VMA(2) );
	case BOTLIB_AI_REPLY_CHAT:
		return botlib_export->ai.BotReplyChat( args[1], VMA(2), args[3], args[4], VMA(5), VMA(6), VMA(7), VMA(8), VMA(9), VMA(10), VMA(11), VMA(12) );
	case BOTLIB_AI_CHAT_LENGTH:
		return botlib_export->ai.BotChatLength( args[1] );
	case BOTLIB_AI_ENTER_CHAT:
		botlib_export->ai.BotEnterChat( args[1], args[2], args[3] );
		return 0;
	case BOTLIB_AI_GET_CHAT_MESSAGE:
		botlib_export->ai.BotGetChatMessage( args[1], VMA(2), args[3] );
		return 0;
	case BOTLIB_AI_STRING_CONTAINS:
		return botlib_export->ai.StringContains( VMA(1), VMA(2), args[3] );
	case BOTLIB_AI_FIND_MATCH:
		return botlib_export->ai.BotFindMatch( VMA(1), VMA(2), args[3] );
	case BOTLIB_AI_MATCH_VARIABLE:
		botlib_export->ai.BotMatchVariable( VMA(1), args[2], VMA(3), args[4] );
		return 0;
	case BOTLIB_AI_UNIFY_WHITE_SPACES:
		botlib_export->ai.UnifyWhiteSpaces( VMA(1) );
		return 0;
	case BOTLIB_AI_REPLACE_SYNONYMS:
		botlib_export->ai.BotReplaceSynonyms( VMA(1), args[2] );
		return 0;
	case BOTLIB_AI_LOAD_CHAT_FILE:
		return botlib_export->ai.BotLoadChatFile( args[1], VMA(2), VMA(3) );
	case BOTLIB_AI_SET_CHAT_GENDER:
		botlib_export->ai.BotSetChatGender( args[1], args[2] );
		return 0;
	case BOTLIB_AI_SET_CHAT_NAME:
		botlib_export->ai.BotSetChatName( args[1], VMA(2), args[3] );
		return 0;

	case BOTLIB_AI_RESET_GOAL_STATE:
		botlib_export->ai.BotResetGoalState( args[1] );
		return 0;
	case BOTLIB_AI_RESET_AVOID_GOALS:
		botlib_export->ai.BotResetAvoidGoals( args[1] );
		return 0;
	case BOTLIB_AI_REMOVE_FROM_AVOID_GOALS:
		botlib_export->ai.BotRemoveFromAvoidGoals( args[1], args[2] );
		return 0;
	case BOTLIB_AI_PUSH_GOAL:
		botlib_export->ai.BotPushGoal( args[1], VMA(2) );
		return 0;
	case BOTLIB_AI_POP_GOAL:
		botlib_export->ai.BotPopGoal( args[1] );
		return 0;
	case BOTLIB_AI_EMPTY_GOAL_STACK:
		botlib_export->ai.BotEmptyGoalStack( args[1] );
		return 0;
	case BOTLIB_AI_DUMP_AVOID_GOALS:
		botlib_export->ai.BotDumpAvoidGoals( args[1] );
		return 0;
	case BOTLIB_AI_DUMP_GOAL_STACK:
		botlib_export->ai.BotDumpGoalStack( args[1] );
		return 0;
	case BOTLIB_AI_GOAL_NAME:
		botlib_export->ai.BotGoalName( args[1], VMA(2), args[3] );
		return 0;
	case BOTLIB_AI_GET_TOP_GOAL:
		return botlib_export->ai.BotGetTopGoal( args[1], VMA(2) );
	case BOTLIB_AI_GET_SECOND_GOAL:
		return botlib_export->ai.BotGetSecondGoal( args[1], VMA(2) );
	case BOTLIB_AI_CHOOSE_LTG_ITEM:
		return botlib_export->ai.BotChooseLTGItem( args[1], VMA(2), VMA(3), args[4] );
	case BOTLIB_AI_CHOOSE_NBG_ITEM:
		return botlib_export->ai.BotChooseNBGItem( args[1], VMA(2), VMA(3), args[4], VMA(5), VMF(6) );
	case BOTLIB_AI_TOUCHING_GOAL:
		return botlib_export->ai.BotTouchingGoal( VMA(1), VMA(2) );
	case BOTLIB_AI_ITEM_GOAL_IN_VIS_BUT_NOT_VISIBLE:
		return botlib_export->ai.BotItemGoalInVisButNotVisible( args[1], VMA(2), VMA(3), VMA(4) );
	case BOTLIB_AI_GET_LEVEL_ITEM_GOAL:
		return botlib_export->ai.BotGetLevelItemGoal( args[1], VMA(2), VMA(3) );
	case BOTLIB_AI_GET_NEXT_CAMP_SPOT_GOAL:
		return botlib_export->ai.BotGetNextCampSpotGoal( args[1], VMA(2) );
	case BOTLIB_AI_GET_MAP_LOCATION_GOAL:
		return botlib_export->ai.BotGetMapLocationGoal( VMA(1), VMA(2) );
	case BOTLIB_AI_AVOID_GOAL_TIME:
		return FloatAsInt( botlib_export->ai.BotAvoidGoalTime( args[1], args[2] ) );
	case BOTLIB_AI_SET_AVOID_GOAL_TIME:
		botlib_export->ai.BotSetAvoidGoalTime( args[1], args[2], VMF(3));
		return 0;
	case BOTLIB_AI_INIT_LEVEL_ITEMS:
		botlib_export->ai.BotInitLevelItems();
		return 0;
	case BOTLIB_AI_UPDATE_ENTITY_ITEMS:
		botlib_export->ai.BotUpdateEntityItems();
		return 0;
	case BOTLIB_AI_LOAD_ITEM_WEIGHTS:
		return botlib_export->ai.BotLoadItemWeights( args[1], VMA(2) );
	case BOTLIB_AI_FREE_ITEM_WEIGHTS:
		botlib_export->ai.BotFreeItemWeights( args[1] );
		return 0;
	case BOTLIB_AI_INTERBREED_GOAL_FUZZY_LOGIC:
		botlib_export->ai.BotInterbreedGoalFuzzyLogic( args[1], args[2], args[3] );
		return 0;
	case BOTLIB_AI_SAVE_GOAL_FUZZY_LOGIC:
		botlib_export->ai.BotSaveGoalFuzzyLogic( args[1], VMA(2) );
		return 0;
	case BOTLIB_AI_MUTATE_GOAL_FUZZY_LOGIC:
		botlib_export->ai.BotMutateGoalFuzzyLogic( args[1], VMF(2) );
		return 0;
	case BOTLIB_AI_ALLOC_GOAL_STATE:
		return botlib_export->ai.BotAllocGoalState( args[1] );
	case BOTLIB_AI_FREE_GOAL_STATE:
		botlib_export->ai.BotFreeGoalState( args[1] );
		return 0;

	case BOTLIB_AI_RESET_MOVE_STATE:
		botlib_export->ai.BotResetMoveState( args[1] );
		return 0;
	case BOTLIB_AI_ADD_AVOID_SPOT:
		botlib_export->ai.BotAddAvoidSpot( args[1], VMA(2), VMF(3), args[4] );
		return 0;
	case BOTLIB_AI_MOVE_TO_GOAL:
		botlib_export->ai.BotMoveToGoal( VMA(1), args[2], VMA(3), args[4] );
		return 0;
	case BOTLIB_AI_MOVE_IN_DIRECTION:
		return botlib_export->ai.BotMoveInDirection( args[1], VMA(2), VMF(3), args[4] );
	case BOTLIB_AI_RESET_AVOID_REACH:
		botlib_export->ai.BotResetAvoidReach( args[1] );
		return 0;
	case BOTLIB_AI_RESET_LAST_AVOID_REACH:
		botlib_export->ai.BotResetLastAvoidReach( args[1] );
		return 0;
	case BOTLIB_AI_REACHABILITY_AREA:
		return botlib_export->ai.BotReachabilityArea( VMA(1), args[2] );
	case BOTLIB_AI_MOVEMENT_VIEW_TARGET:
		return botlib_export->ai.BotMovementViewTarget( args[1], VMA(2), args[3], VMF(4), VMA(5) );
	case BOTLIB_AI_PREDICT_VISIBLE_POSITION:
		return botlib_export->ai.BotPredictVisiblePosition( VMA(1), args[2], VMA(3), args[4], VMA(5) );
	case BOTLIB_AI_ALLOC_MOVE_STATE:
		return botlib_export->ai.BotAllocMoveState();
	case BOTLIB_AI_FREE_MOVE_STATE:
		botlib_export->ai.BotFreeMoveState( args[1] );
		return 0;
	case BOTLIB_AI_INIT_MOVE_STATE:
		botlib_export->ai.BotInitMoveState( args[1], VMA(2) );
		return 0;

	case BOTLIB_AI_CHOOSE_BEST_FIGHT_WEAPON:
		return botlib_export->ai.BotChooseBestFightWeapon( args[1], VMA(2) );
	case BOTLIB_AI_GET_WEAPON_INFO:
		botlib_export->ai.BotGetWeaponInfo( args[1], args[2], VMA(3) );
		return 0;
	case BOTLIB_AI_LOAD_WEAPON_WEIGHTS:
		return botlib_export->ai.BotLoadWeaponWeights( args[1], VMA(2) );
	case BOTLIB_AI_ALLOC_WEAPON_STATE:
		return botlib_export->ai.BotAllocWeaponState();
	case BOTLIB_AI_FREE_WEAPON_STATE:
		botlib_export->ai.BotFreeWeaponState( args[1] );
		return 0;
	case BOTLIB_AI_RESET_WEAPON_STATE:
		botlib_export->ai.BotResetWeaponState( args[1] );
		return 0;

	case BOTLIB_AI_GENETIC_PARENTS_AND_CHILD_SELECTION:
		return botlib_export->ai.GeneticParentsAndChildSelection(args[1], VMA(2), VMA(3), VMA(4), VMA(5));

	case TRAP_MEMSET:
		Com_Memset( VMA(1), args[2], args[3] );
		return 0;

	case TRAP_MEMCPY:
		Com_Memcpy( VMA(1), VMA(2), args[3] );
		return 0;

	case TRAP_STRNCPY:
		strncpy( VMA(1), VMA(2), args[3] );
		return args[1];

	case TRAP_SIN:
		return FloatAsInt( sin( VMF(1) ) );

	case TRAP_COS:
		return FloatAsInt( cos( VMF(1) ) );

	case TRAP_ATAN2:
		return FloatAsInt( atan2( VMF(1), VMF(2) ) );

	case TRAP_SQRT:
		return FloatAsInt( sqrt( VMF(1) ) );

	case TRAP_MATRIXMULTIPLY:
		MatrixMultiply( VMA(1), VMA(2), VMA(3) );
		return 0;

	case TRAP_ANGLEVECTORS:
		AngleVectors( VMA(1), VMA(2), VMA(3), VMA(4) );
		return 0;

	case TRAP_PERPENDICULARVECTOR:
		PerpendicularVector( VMA(1), VMA(2) );
		return 0;

	case TRAP_FLOOR:
		return FloatAsInt( floor( VMF(1) ) );

	case TRAP_CEIL:
		return FloatAsInt( ceil( VMF(1) ) );

	case G_DEEPMIND_CALLBACK:
		return dmlab_callback( args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8], args[9], args[10], args[11], args[12], args[13] );

	default:
		Com_Error( ERR_DROP, "Bad game system trap: %ld", (long int) args[0] );
	}
	return 0;
}
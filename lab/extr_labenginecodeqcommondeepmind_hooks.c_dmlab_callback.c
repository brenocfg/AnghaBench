#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_5__ vec3_t ;
struct TYPE_17__ {double width; int height; int y; int fov_x; double fov_y; int /*<<< orphan*/  viewaxis; int /*<<< orphan*/  vieworg; } ;
typedef  TYPE_6__ refdef_t ;
struct TYPE_18__ {int eFlags; int /*<<< orphan*/  viewangles; int /*<<< orphan*/  velocity; int /*<<< orphan*/  origin; int /*<<< orphan*/  viewheight; int /*<<< orphan*/  weapon; int /*<<< orphan*/  powerups; int /*<<< orphan*/  stats; int /*<<< orphan*/  persistant; int /*<<< orphan*/  ammo; int /*<<< orphan*/  clientNum; } ;
typedef  TYPE_7__ playerState_t ;
struct TYPE_12__ {int /*<<< orphan*/  (* add ) (int /*<<< orphan*/ ,intptr_t,intptr_t,intptr_t,intptr_t,void*,void*) ;int /*<<< orphan*/  (* clear ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_14__ {int (* update_spawn_vars ) (int /*<<< orphan*/ ,void*,void*,void*,void*) ;int (* make_extra_entities ) (int /*<<< orphan*/ ) ;int (* find_item ) (int /*<<< orphan*/ ,void*,void*) ;int (* item_count ) (int /*<<< orphan*/ ) ;int (* item ) (int /*<<< orphan*/ ,intptr_t,void*,intptr_t,void*,intptr_t,void*,intptr_t,void*,void*,void*,void*) ;int (* register_dynamic_items ) (int /*<<< orphan*/ ) ;int (* dynamic_spawn_entity_count ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* read_dynamic_spawn_entity ) (int /*<<< orphan*/ ,intptr_t,void*,void*,void*,void*) ;int /*<<< orphan*/  (* clear_dynamic_spawn_entities ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* read_dynamic_item_name ) (int /*<<< orphan*/ ,intptr_t,void*) ;int /*<<< orphan*/  (* clear_items ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* read_extra_entity ) (int /*<<< orphan*/ ,intptr_t,void*,void*,void*,void*) ;} ;
struct TYPE_15__ {int (* can_pickup ) (int /*<<< orphan*/ ,intptr_t,int /*<<< orphan*/ ) ;int (* override_pickup ) (int /*<<< orphan*/ ,intptr_t,void*,int /*<<< orphan*/ ) ;int (* can_trigger ) (int /*<<< orphan*/ ,intptr_t,void*,int /*<<< orphan*/ ) ;int (* override_trigger ) (int /*<<< orphan*/ ,intptr_t,void*,int /*<<< orphan*/ ) ;int (* reward_override ) (int /*<<< orphan*/ ,void*,intptr_t,intptr_t,void*,void*,intptr_t) ;int (* make_screen_messages ) (int /*<<< orphan*/ ,intptr_t,intptr_t,intptr_t,intptr_t) ;int (* make_filled_rectangles ) (int /*<<< orphan*/ ,intptr_t,intptr_t) ;int (* team_select ) (int /*<<< orphan*/ ,intptr_t,void*) ;int (* update_player_info ) (int /*<<< orphan*/ ,intptr_t,void*,intptr_t) ;int /*<<< orphan*/  (* new_client_info ) (int /*<<< orphan*/ ,intptr_t,void*,void*) ;int /*<<< orphan*/  (* custom_view ) (int /*<<< orphan*/ ,double*,int*,int /*<<< orphan*/ ,TYPE_5__,int*) ;TYPE_1__ entities; int /*<<< orphan*/  (* update_inventory ) (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* game_event ) (int /*<<< orphan*/ ,void*,intptr_t,void*) ;int /*<<< orphan*/  (* lua_mover ) (int /*<<< orphan*/ ,intptr_t,void*,void*,void*,void*,void*) ;int /*<<< orphan*/  (* get_filled_rectangle ) (int /*<<< orphan*/ ,intptr_t,void*,void*,void*,void*,void*) ;int /*<<< orphan*/  (* get_screen_message ) (int /*<<< orphan*/ ,intptr_t,void*,void*,void*,void*,void*,void*) ;int /*<<< orphan*/  (* player_state ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,intptr_t,intptr_t,int /*<<< orphan*/ ,int,int) ;int /*<<< orphan*/  (* trigger_lookat ) (int /*<<< orphan*/ ,intptr_t,intptr_t,void*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_map_finished ) (int /*<<< orphan*/ ,intptr_t) ;TYPE_3__ pickups; } ;
struct TYPE_13__ {int (* total_engine_time_msec ) () ;int (* player_score ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* screen_shape ) (int*,int*,int*,int*) ;} ;
struct TYPE_19__ {int /*<<< orphan*/  userdata; TYPE_4__ hooks; TYPE_2__ calls; int /*<<< orphan*/  context; } ;
typedef  TYPE_8__ DeepmindContext ;

/* Variables and functions */
 int /*<<< orphan*/  AnglesToAxis (TYPE_5__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*,int) ; 
#define  DEEPMIND_CAN_PICKUP 162 
#define  DEEPMIND_CAN_TRIGGER 161 
#define  DEEPMIND_CLEAR_DYNAMIC_SPAWN_ENTITIES 160 
#define  DEEPMIND_CLEAR_ITEMS 159 
#define  DEEPMIND_CUSTOM_VIEW 158 
#define  DEEPMIND_DYNAMIC_SPAWN_ENTITY_COUNT 157 
#define  DEEPMIND_ENTITIES_ADD 156 
#define  DEEPMIND_ENTITIES_CLEAR 155 
#define  DEEPMIND_FIND_ITEM 154 
#define  DEEPMIND_FINISH_MAP 153 
#define  DEEPMIND_GAME_EVENT 152 
#define  DEEPMIND_GET_FILLED_RECTANGLE 151 
#define  DEEPMIND_GET_SCREEN_MESSAGE 150 
#define  DEEPMIND_ITEM 149 
#define  DEEPMIND_ITEM_COUNT 148 
#define  DEEPMIND_LUA_MOVER 147 
#define  DEEPMIND_MAKE_EXTRA_ENTITIES 146 
#define  DEEPMIND_MAKE_FILLED_RECTANGLES 145 
#define  DEEPMIND_MAKE_SCREEN_MESSAGES 144 
#define  DEEPMIND_NEW_CLIENT_INFO 143 
#define  DEEPMIND_OVERRIDE_LOOKAT 142 
#define  DEEPMIND_OVERRIDE_PICKUP 141 
#define  DEEPMIND_OVERRIDE_TRIGGER 140 
#define  DEEPMIND_PLAYER_SCORE 139 
#define  DEEPMIND_READ_DYNAMIC_ITEM_NAME 138 
#define  DEEPMIND_READ_DYNAMIC_SPAWN_ENTITY 137 
#define  DEEPMIND_READ_EXTRA_ENTITY 136 
#define  DEEPMIND_REGISTER_DYNAMIC_ITEMS 135 
#define  DEEPMIND_REWARD_OVERRIDE 134 
#define  DEEPMIND_SET_PLAYER_STATE 133 
#define  DEEPMIND_SPAWN_INVENTORY 132 
#define  DEEPMIND_TEAM_SELECT 131 
#define  DEEPMIND_UPDATE_INVENTORY 130 
#define  DEEPMIND_UPDATE_PLAYER_INFO 129 
#define  DEEPMIND_UPDATE_SPAWN_VARS 128 
 int EF_TELEPORT_BIT ; 
 int /*<<< orphan*/  ERR_DROP ; 
 int /*<<< orphan*/  MAX_PERSISTANT ; 
 int /*<<< orphan*/  MAX_POWERUPS ; 
 int /*<<< orphan*/  MAX_STATS ; 
 int /*<<< orphan*/  MAX_WEAPONS ; 
 double M_PI ; 
 void* VM_ArgPtr (intptr_t) ; 
 double atan (double) ; 
 TYPE_8__* dmlab_context () ; 
 int qfalse ; 
 int qtrue ; 
 int stub1 (int /*<<< orphan*/ ,void*,void*,void*,void*) ; 
 int stub10 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub12 (int /*<<< orphan*/ ,intptr_t,void*,void*,void*,void*) ; 
 int /*<<< orphan*/  stub13 (int /*<<< orphan*/ ,intptr_t) ; 
 int stub14 (int /*<<< orphan*/ ,intptr_t,int /*<<< orphan*/ ) ; 
 int stub15 (int /*<<< orphan*/ ,intptr_t,void*,int /*<<< orphan*/ ) ; 
 int stub16 (int /*<<< orphan*/ ,intptr_t,void*,int /*<<< orphan*/ ) ; 
 int stub17 (int /*<<< orphan*/ ,intptr_t,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub18 (int /*<<< orphan*/ ,intptr_t,intptr_t,void*,int /*<<< orphan*/ ) ; 
 int stub19 (int /*<<< orphan*/ ,void*,intptr_t,intptr_t,void*,void*,intptr_t) ; 
 int stub2 (int /*<<< orphan*/ ) ; 
 int stub20 () ; 
 int /*<<< orphan*/  stub21 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,intptr_t,intptr_t,int /*<<< orphan*/ ,int,int) ; 
 int stub22 (int /*<<< orphan*/ ,intptr_t,intptr_t,intptr_t,intptr_t) ; 
 int /*<<< orphan*/  stub23 (int /*<<< orphan*/ ,intptr_t,void*,void*,void*,void*,void*,void*) ; 
 int stub24 (int /*<<< orphan*/ ,intptr_t,intptr_t) ; 
 int /*<<< orphan*/  stub25 (int /*<<< orphan*/ ,intptr_t,void*,void*,void*,void*,void*) ; 
 int stub26 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub27 (int /*<<< orphan*/ ,intptr_t,void*,void*,void*,void*,void*) ; 
 int /*<<< orphan*/  stub28 (int /*<<< orphan*/ ,void*,intptr_t,void*) ; 
 int /*<<< orphan*/  stub29 (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,intptr_t,void*,void*,void*,void*) ; 
 int stub30 (int /*<<< orphan*/ ,intptr_t,void*) ; 
 int stub31 (int /*<<< orphan*/ ,intptr_t,void*,intptr_t) ; 
 int /*<<< orphan*/  stub32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub33 (int /*<<< orphan*/ ,intptr_t,intptr_t,intptr_t,intptr_t,void*,void*) ; 
 int /*<<< orphan*/  stub34 (int /*<<< orphan*/ ,double*,int*,int /*<<< orphan*/ ,TYPE_5__,int*) ; 
 int /*<<< orphan*/  stub35 (int*,int*,int*,int*) ; 
 int /*<<< orphan*/  stub36 (int /*<<< orphan*/ ,intptr_t,void*,void*) ; 
 int stub4 (int /*<<< orphan*/ ,void*,void*) ; 
 int stub5 (int /*<<< orphan*/ ) ; 
 int stub6 (int /*<<< orphan*/ ,intptr_t,void*,intptr_t,void*,intptr_t,void*,intptr_t,void*,void*,void*,void*) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ) ; 
 int stub8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ ,intptr_t,void*) ; 
 double tan (double) ; 

int dmlab_callback(
    int dm_callnum, intptr_t a1, intptr_t a2, intptr_t a3, intptr_t a4,
    intptr_t a5, intptr_t a6, intptr_t a7, intptr_t a8, intptr_t a9,
    intptr_t a10, intptr_t a11, intptr_t a12) {
  DeepmindContext* ctx = dmlab_context();
  switch (dm_callnum) {
    case DEEPMIND_UPDATE_SPAWN_VARS:
      return ctx->hooks.pickups.update_spawn_vars(ctx->userdata,
                                          /*spawn_var_chars=*/VM_ArgPtr(a1),
                                          /*num_spawn_var_chars=*/VM_ArgPtr(a2),
                                          /*spawn_vars_offsets=*/VM_ArgPtr(a3),
                                          /*num_spawn_vars=*/VM_ArgPtr(a4));

    case DEEPMIND_MAKE_EXTRA_ENTITIES:
      return ctx->hooks.pickups.make_extra_entities(ctx->userdata);
    case DEEPMIND_READ_EXTRA_ENTITY:
      ctx->hooks.pickups.read_extra_entity(ctx->userdata,
                                   /*entity_index=*/a1,
                                   /*spawn_var_chars=*/VM_ArgPtr(a2),
                                   /*num_spawn_var_chars=*/VM_ArgPtr(a3),
                                   /*spawn_vars_offsets=*/VM_ArgPtr(a4),
                                   /*num_spawn_vars=*/VM_ArgPtr(a5));
      return 0;
    case DEEPMIND_FIND_ITEM:
      return ctx->hooks.pickups.find_item(ctx->userdata, /*class_name=*/VM_ArgPtr(a1),
                                  /*index=*/VM_ArgPtr(a2));
    case DEEPMIND_ITEM_COUNT:
      return ctx->hooks.pickups.item_count(ctx->userdata);
    case DEEPMIND_ITEM:
      return ctx->hooks.pickups.item(
          ctx->userdata, /*index=*/a1, /*item_name=*/VM_ArgPtr(a2),
          /*max_item_name=*/a3,
          /*class_name=*/VM_ArgPtr(a4), /*max_class_name=*/a5,
          /*model_name=*/VM_ArgPtr(a6), /*max_model_name=*/a7,
          /*quantity=*/VM_ArgPtr(a8), /*type=*/VM_ArgPtr(a9),
          /*tag=*/VM_ArgPtr(a10),
          /*move_type=*/VM_ArgPtr(a11));
    case DEEPMIND_CLEAR_ITEMS:
      ctx->hooks.pickups.clear_items(ctx->userdata);
      return 1;

    case DEEPMIND_REGISTER_DYNAMIC_ITEMS:
      return ctx->hooks.pickups.register_dynamic_items(ctx->userdata);
    case DEEPMIND_READ_DYNAMIC_ITEM_NAME:
      ctx->hooks.pickups.read_dynamic_item_name(ctx->userdata,
                                                /*item_index=*/a1,
                                                /*item_name=*/VM_ArgPtr(a2));
      return 0;

    case DEEPMIND_DYNAMIC_SPAWN_ENTITY_COUNT:
      return ctx->hooks.pickups.dynamic_spawn_entity_count(ctx->userdata);
    case DEEPMIND_CLEAR_DYNAMIC_SPAWN_ENTITIES:
      ctx->hooks.pickups.clear_dynamic_spawn_entities(ctx->userdata);
      return 0;
    case DEEPMIND_READ_DYNAMIC_SPAWN_ENTITY:
      ctx->hooks.pickups.read_dynamic_spawn_entity(ctx->userdata,
                             /*entity_index=*/a1,
                             /*spawn_var_chars=*/VM_ArgPtr(a2),
                             /*num_spawn_var_chars=*/VM_ArgPtr(a3),
                             /*spawn_vars_offsets=*/VM_ArgPtr(a4),
                             /*num_spawn_vars=*/VM_ArgPtr(a5));
      return 0;
    case DEEPMIND_FINISH_MAP:
      ctx->hooks.set_map_finished(ctx->userdata, /*map_finished=*/a1);
      return 1;
    case DEEPMIND_CAN_PICKUP: {
      const playerState_t* ps = VM_ArgPtr(a2);
      return ctx->hooks.can_pickup(ctx->userdata, /*entity_id=*/a1,
                                   /*player_id=*/ps->clientNum);
    }
    case DEEPMIND_OVERRIDE_PICKUP: {
      const playerState_t* ps = VM_ArgPtr(a3);
      return ctx->hooks.override_pickup(ctx->userdata, /*entity_id=*/a1,
                                        /*respawn=*/VM_ArgPtr(a2),
                                        /*player_id=*/ps->clientNum);
    }
    case DEEPMIND_CAN_TRIGGER: {
      const playerState_t* ps = VM_ArgPtr(a3);
      return ctx->hooks.can_trigger(ctx->userdata, /*entity_id=*/a1,
                                    /*target_name=*/VM_ArgPtr(a2),
                                    /*player_id=*/ps->clientNum);
    }
    case DEEPMIND_OVERRIDE_TRIGGER: {
      const playerState_t* ps = VM_ArgPtr(a3);
      return ctx->hooks.override_trigger(ctx->userdata, /*entity_id=*/a1,
                                         /*target_name=*/VM_ArgPtr(a2),
                                         /*player_id=*/ps->clientNum);
    }
    case DEEPMIND_OVERRIDE_LOOKAT: {
      const playerState_t* ps = VM_ArgPtr(a4);
      ctx->hooks.trigger_lookat(ctx->userdata, /*entity_id=*/a1,
                                /*looked_at=*/a2,
                                /*position=*/VM_ArgPtr(a3),
                                /*player_id=*/ps->clientNum);
    } break;
    case DEEPMIND_REWARD_OVERRIDE:
      return ctx->hooks.reward_override(ctx->userdata,
                                        /*reason=*/VM_ArgPtr(a1),
                                        /*player_id=*/a2,
                                        /*team=*/a3,
                                        /*other_player_id_opt=*/VM_ArgPtr(a4),
                                        /*origin=*/VM_ArgPtr(a5),
                                        /*score=*/a6);
    case DEEPMIND_SET_PLAYER_STATE: {
      const playerState_t* ps = VM_ArgPtr(a1);
      int timestamp_msec = ctx->calls.total_engine_time_msec();
      ctx->hooks.player_state(
          ctx->userdata, ps->origin, ps->velocity, ps->viewangles,
          ps->viewheight,
          /*eyePos=*/VM_ArgPtr(a2),
          /*team_score=*/a3,
          /*other_team_score=*/a4, ps->clientNum,
          /*teleporter_flip=*/(ps->eFlags & EF_TELEPORT_BIT),
          timestamp_msec);
      break;
    }
    case DEEPMIND_MAKE_SCREEN_MESSAGES:
      return ctx->hooks.make_screen_messages(ctx->userdata, /*width=*/a1,
                                             /*height=*/a2, /*line_height=*/a3,
                                             /*string_buffer_size=*/a4);
    case DEEPMIND_GET_SCREEN_MESSAGE:
      ctx->hooks.get_screen_message(
          ctx->userdata, /*message_id=*/a1, /*buffer=*/VM_ArgPtr(a2),
          /*x=*/VM_ArgPtr(a3),
          /*y=*/VM_ArgPtr(a4), /*shadow=*/VM_ArgPtr(a5),
          /*align_l0_r1_c2=*/VM_ArgPtr(a6),
          /*rgba=*/VM_ArgPtr(a7));
      break;
    case DEEPMIND_MAKE_FILLED_RECTANGLES:
      return ctx->hooks.make_filled_rectangles(ctx->userdata,
                                               /*screen_width=*/a1,
                                               /*screen_height=*/a2);
    case DEEPMIND_GET_FILLED_RECTANGLE:
      ctx->hooks.get_filled_rectangle(
          ctx->userdata, /*rectangle_id=*/a1, /*x=*/VM_ArgPtr(a2),
          /*y=*/VM_ArgPtr(a3),
          /*width=*/VM_ArgPtr(a4), /*height=*/VM_ArgPtr(a5),
          /*rgba=*/VM_ArgPtr(a6));
      break;
    case DEEPMIND_PLAYER_SCORE:
      return ctx->calls.player_score(ctx->context);
    case DEEPMIND_LUA_MOVER:
      ctx->hooks.lua_mover(
          ctx->userdata, /*entity_id=*/a1, /*entity_pos=*/VM_ArgPtr(a2),
          /*player_pos=*/VM_ArgPtr(a3), /*player_vel=*/VM_ArgPtr(a4),
          /*player_pos_delta=*/VM_ArgPtr(a5),
          /*player_vel_delta=*/VM_ArgPtr(a6));
      break;
    case DEEPMIND_GAME_EVENT:
      ctx->hooks.game_event(ctx->userdata, /*event_name=*/VM_ArgPtr(a1),
                            /*count=*/a2,
                            /*data=*/VM_ArgPtr(a3));
      break;
    case DEEPMIND_SPAWN_INVENTORY:
    case DEEPMIND_UPDATE_INVENTORY: {
      playerState_t* ps = VM_ArgPtr(a1);
      ctx->hooks.update_inventory(
          ctx->userdata,
          /*is_spawning=*/dm_callnum == DEEPMIND_SPAWN_INVENTORY,
          /*is_bot=*/a2 != 0,
          /*player_id=*/ps->clientNum,
          /*gadget_count=*/MAX_WEAPONS,
          /*gadget_inventory=*/ps->ammo,
          /*persistent_count=*/MAX_PERSISTANT,
          /*persistent=*/ps->persistant,
          /*stat_count=*/MAX_STATS,
          /*stats_inventory=*/ps->stats,
          /*powerup_count=*/MAX_POWERUPS,
          /*powerup_time=*/ps->powerups,
          /*gadget_held=*/ps->weapon,
          /*height=*/ps->viewheight,
          /*position=*/ps->origin,
          /*velocity=*/ps->velocity,
          /*view_angles=*/ps->viewangles);
      break;
    }
    case DEEPMIND_TEAM_SELECT:
      return ctx->hooks.team_select(ctx->userdata,
                                    /*player_id=*/a1,
                                    /*player_name=*/VM_ArgPtr(a2));
      break;
    case DEEPMIND_UPDATE_PLAYER_INFO:
      return ctx->hooks.update_player_info(ctx->userdata,
                                           /*player_id=*/a1,
                                           /*info=*/VM_ArgPtr(a2),
                                           /*info_size=*/a3);
      break;
    case DEEPMIND_ENTITIES_CLEAR:
      ctx->hooks.entities.clear(ctx->userdata);
      break;
    case DEEPMIND_ENTITIES_ADD:
      ctx->hooks.entities.add(ctx->userdata, /*player_id=*/a1,
                              /*user_id=*/a2,
                              /*type=*/a3,
                              /*flags=*/a4,
                              /*position=*/VM_ArgPtr(a5),
                              /*classname=*/VM_ArgPtr(a6));
      break;
    case DEEPMIND_CUSTOM_VIEW: {
      refdef_t* camera = VM_ArgPtr(a1);
      vec3_t angles = {0, 0, 0};
      bool render_player;
      ctx->hooks.custom_view(ctx->userdata, &camera->width, &camera->height,
                             camera->vieworg, angles, &render_player);
      AnglesToAxis(angles, camera->viewaxis);
      int width, height, buff_width, buff_height;
      ctx->calls.screen_shape(&width, &height, &buff_width, &buff_height);
      camera->y = buff_height - camera->height;
      double aspect = (double)camera->height / camera->width;
      camera->fov_x = 90;
      double fov_x_rad = camera->fov_x * (M_PI / 180.0);
      double fov_y_rad = 2.0 * atan(aspect * tan(fov_x_rad * 0.5));
      camera->fov_y = (180.0 / M_PI) * fov_y_rad;
      return (render_player) ? qtrue : qfalse;
    }
    case DEEPMIND_NEW_CLIENT_INFO:
      ctx->hooks.new_client_info(ctx->userdata, a1, VM_ArgPtr(a2),
                                 VM_ArgPtr(a3));
      break;
    default:
      Com_Error(ERR_DROP, "DeepMind system call %d not implemented\n",
                dm_callnum);
  }

  return 0;
}
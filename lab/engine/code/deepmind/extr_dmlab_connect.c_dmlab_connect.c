#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dmlabRecordingContext ;
struct TYPE_17__ {char* runfiles_path; int /*<<< orphan*/  optional_temp_folder; int /*<<< orphan*/  read_only_file_system; int /*<<< orphan*/  file_reader_override; int /*<<< orphan*/  level_cache_params; } ;
struct TYPE_13__ {int /*<<< orphan*/  render_custom_view; int /*<<< orphan*/  is_map_loading; int /*<<< orphan*/  in_fov; int /*<<< orphan*/  raycast; int /*<<< orphan*/  update_rgba_texture; int /*<<< orphan*/  save_model; int /*<<< orphan*/  serialise_model; int /*<<< orphan*/  serialised_model_size; int /*<<< orphan*/  load_model; int /*<<< orphan*/  deserialise_model; int /*<<< orphan*/  total_time_seconds; int /*<<< orphan*/  total_engine_time_msec; int /*<<< orphan*/  engine_frame_period_msec; int /*<<< orphan*/  execute_console_command; int /*<<< orphan*/  add_bot; int /*<<< orphan*/  screen_shape; int /*<<< orphan*/  add_score; int /*<<< orphan*/  player_score; } ;
struct TYPE_16__ {TYPE_3__* context; TYPE_2__ calls; } ;
struct TYPE_15__ {int /*<<< orphan*/  release_context; int /*<<< orphan*/  advance; int /*<<< orphan*/  act_text; int /*<<< orphan*/  act_continuous; int /*<<< orphan*/  act_discrete; int /*<<< orphan*/  act; int /*<<< orphan*/  event; int /*<<< orphan*/  event_count; int /*<<< orphan*/  observation; int /*<<< orphan*/  fps; int /*<<< orphan*/  event_type_name; int /*<<< orphan*/  event_type_count; int /*<<< orphan*/  observation_spec; int /*<<< orphan*/  observation_name; int /*<<< orphan*/  observation_count; int /*<<< orphan*/  action_text_name; int /*<<< orphan*/  action_text_count; int /*<<< orphan*/  action_continuous_bounds; int /*<<< orphan*/  action_continuous_name; int /*<<< orphan*/  action_continuous_count; int /*<<< orphan*/  action_discrete_bounds; int /*<<< orphan*/  action_discrete_name; int /*<<< orphan*/  action_discrete_count; int /*<<< orphan*/  environment_name; int /*<<< orphan*/  error_message; int /*<<< orphan*/  start; int /*<<< orphan*/  list_property; int /*<<< orphan*/  read_property; int /*<<< orphan*/  write_property; int /*<<< orphan*/  init; int /*<<< orphan*/  setting; } ;
struct TYPE_12__ {int enabled; } ;
struct TYPE_14__ {int use_local_level_cache; int use_global_level_cache; int width; int height; int* map_frame_number_shape; TYPE_5__* dm_ctx; int /*<<< orphan*/  runfiles_path; TYPE_1__ pbos; scalar_t__ map_frame_number_observation; int /*<<< orphan*/ * recording_ctx; int /*<<< orphan*/  level_cache_params; } ;
typedef  TYPE_3__ GameContext ;
typedef  TYPE_4__ EnvCApi ;
typedef  TYPE_5__ DeepmindContext ;
typedef  TYPE_6__ DeepMindLabLaunchParams ;

/* Variables and functions */
 int /*<<< orphan*/  Q_strncpyz (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  add_bot ; 
 int /*<<< orphan*/  call_add_score ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  dmlab_act ; 
 int /*<<< orphan*/  dmlab_act_continuous ; 
 int /*<<< orphan*/  dmlab_act_discrete ; 
 int /*<<< orphan*/  dmlab_act_text ; 
 int /*<<< orphan*/  dmlab_action_continuous_bounds ; 
 int /*<<< orphan*/  dmlab_action_continuous_count ; 
 int /*<<< orphan*/  dmlab_action_continuous_name ; 
 int /*<<< orphan*/  dmlab_action_discrete_bounds ; 
 int /*<<< orphan*/  dmlab_action_discrete_count ; 
 int /*<<< orphan*/  dmlab_action_discrete_name ; 
 int /*<<< orphan*/  dmlab_action_text_count ; 
 int /*<<< orphan*/  dmlab_action_text_name ; 
 int /*<<< orphan*/  dmlab_advance ; 
 int dmlab_create_context (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmlab_deserialise_model ; 
 int /*<<< orphan*/  dmlab_destroy_context ; 
 int /*<<< orphan*/  dmlab_environment_name ; 
 int /*<<< orphan*/  dmlab_error_message ; 
 int /*<<< orphan*/  dmlab_event ; 
 int /*<<< orphan*/  dmlab_event_count ; 
 int /*<<< orphan*/  dmlab_event_type_count ; 
 int /*<<< orphan*/  dmlab_event_type_name ; 
 int /*<<< orphan*/  dmlab_fps ; 
 int /*<<< orphan*/  dmlab_in_fov ; 
 int /*<<< orphan*/  dmlab_init ; 
 int /*<<< orphan*/  dmlab_is_map_loading ; 
 int /*<<< orphan*/  dmlab_list_property ; 
 int /*<<< orphan*/  dmlab_load_model ; 
 int /*<<< orphan*/  dmlab_observation ; 
 int /*<<< orphan*/  dmlab_observation_count ; 
 int /*<<< orphan*/  dmlab_observation_name ; 
 int /*<<< orphan*/  dmlab_observation_spec ; 
 int /*<<< orphan*/  dmlab_raycast ; 
 int /*<<< orphan*/  dmlab_read_property ; 
 int /*<<< orphan*/  dmlab_render_custom_view ; 
 int /*<<< orphan*/  dmlab_save_model ; 
 int /*<<< orphan*/  dmlab_serialise_model ; 
 int /*<<< orphan*/  dmlab_serialised_model_size ; 
 int /*<<< orphan*/  dmlab_setting ; 
 int /*<<< orphan*/  dmlab_start ; 
 int /*<<< orphan*/  dmlab_update_rgba_texture ; 
 int /*<<< orphan*/  dmlab_write_property ; 
 int /*<<< orphan*/  engine_frame_period_msec ; 
 int /*<<< orphan*/  execute_console_command ; 
 TYPE_5__* get_context_once () ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  player_score ; 
 int /*<<< orphan*/  screen_shape ; 
 int /*<<< orphan*/  total_engine_time_msec ; 
 int /*<<< orphan*/  total_time_seconds ; 

int dmlab_connect(const DeepMindLabLaunchParams* params, EnvCApi* env_c_api,
                  void** context) {
  DeepmindContext* dm_ctx = get_context_once();
  if (dm_ctx == NULL) {
    return 1;
  }

  GameContext* gc = calloc(1, sizeof(GameContext));
  if (gc == NULL) {
    return 2;
  }

  if (params == NULL) {
    return 3;
  }

  if (params->runfiles_path == NULL || params->runfiles_path[0] == '\0') {
    return 4;
  }

  dmlabRecordingContext* rcxt = calloc(1, sizeof(dmlabRecordingContext));
  if (rcxt == NULL) {
    return 1;
  }

  *context = gc;

  Q_strncpyz(gc->runfiles_path, params->runfiles_path,
             sizeof(gc->runfiles_path));

  // Disable local level cache by default.
  gc->use_local_level_cache = false;
  gc->use_global_level_cache = true;
  gc->level_cache_params = params->level_cache_params;
  gc->width = 320;
  gc->height = 240;
  gc->dm_ctx = dm_ctx;
  gc->recording_ctx = rcxt;
  gc->map_frame_number_shape[0] = 1;
  gc->map_frame_number_observation = 0;
  gc->pbos.enabled = true;

  memset(env_c_api, 0, sizeof(EnvCApi));

  env_c_api->setting = dmlab_setting;
  env_c_api->init = dmlab_init;
  env_c_api->write_property = dmlab_write_property;
  env_c_api->read_property = dmlab_read_property;
  env_c_api->list_property = dmlab_list_property;
  env_c_api->start = dmlab_start;
  env_c_api->error_message = dmlab_error_message;
  env_c_api->environment_name = dmlab_environment_name;
  env_c_api->action_discrete_count = dmlab_action_discrete_count;
  env_c_api->action_discrete_name = dmlab_action_discrete_name;
  env_c_api->action_discrete_bounds = dmlab_action_discrete_bounds;
  env_c_api->action_continuous_count = dmlab_action_continuous_count;
  env_c_api->action_continuous_name = dmlab_action_continuous_name;
  env_c_api->action_continuous_bounds = dmlab_action_continuous_bounds;
  env_c_api->action_text_count = dmlab_action_text_count;
  env_c_api->action_text_name = dmlab_action_text_name;
  env_c_api->observation_count = dmlab_observation_count;
  env_c_api->observation_name = dmlab_observation_name;
  env_c_api->observation_spec = dmlab_observation_spec;
  env_c_api->event_type_count = dmlab_event_type_count;
  env_c_api->event_type_name = dmlab_event_type_name;
  env_c_api->fps = dmlab_fps;
  env_c_api->observation = dmlab_observation;
  env_c_api->event_count = dmlab_event_count;
  env_c_api->event = dmlab_event;
  env_c_api->act = dmlab_act;
  env_c_api->act_discrete = dmlab_act_discrete;
  env_c_api->act_continuous = dmlab_act_continuous;
  env_c_api->act_text = dmlab_act_text;
  env_c_api->advance = dmlab_advance;
  env_c_api->release_context = dmlab_destroy_context;
  gc->dm_ctx->calls.player_score = player_score;
  gc->dm_ctx->calls.add_score = call_add_score;
  gc->dm_ctx->calls.screen_shape = screen_shape;
  gc->dm_ctx->calls.add_bot = add_bot;
  gc->dm_ctx->calls.execute_console_command = execute_console_command;
  gc->dm_ctx->calls.engine_frame_period_msec = engine_frame_period_msec;
  gc->dm_ctx->calls.total_engine_time_msec = total_engine_time_msec;
  gc->dm_ctx->calls.total_time_seconds = total_time_seconds;
  gc->dm_ctx->calls.deserialise_model = dmlab_deserialise_model;
  gc->dm_ctx->calls.load_model = dmlab_load_model;
  gc->dm_ctx->calls.serialised_model_size = dmlab_serialised_model_size;
  gc->dm_ctx->calls.serialise_model = dmlab_serialise_model;
  gc->dm_ctx->calls.save_model = dmlab_save_model;
  gc->dm_ctx->calls.update_rgba_texture = dmlab_update_rgba_texture;
  gc->dm_ctx->calls.raycast = dmlab_raycast;
  gc->dm_ctx->calls.in_fov = dmlab_in_fov;
  gc->dm_ctx->calls.is_map_loading = dmlab_is_map_loading;
  gc->dm_ctx->calls.render_custom_view = dmlab_render_custom_view;
  gc->dm_ctx->context = gc;
  return dmlab_create_context(gc->runfiles_path, gc->dm_ctx,
                              params->file_reader_override,
                              params->read_only_file_system,
                              params->optional_temp_folder);
}
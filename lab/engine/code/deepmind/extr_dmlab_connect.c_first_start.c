#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* (* get_temporary_folder ) (int /*<<< orphan*/ ) ;char const* (* game_type ) (int /*<<< orphan*/ ) ;char* (* replace_command_line ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  userdata; TYPE_1__ hooks; } ;
struct TYPE_7__ {int /*<<< orphan*/  supported; } ;
struct TYPE_8__ {TYPE_2__ pbos; int /*<<< orphan*/  command_line; int /*<<< orphan*/  runfiles_path; TYPE_4__* dm_ctx; } ;
typedef  TYPE_3__ GameContext ;
typedef  TYPE_4__ DeepmindContext ;

/* Variables and functions */
 int /*<<< orphan*/  CON_Init () ; 
 int /*<<< orphan*/  Com_Init (char*) ; 
 int /*<<< orphan*/  NET_Init () ; 
 int /*<<< orphan*/  Q_strcat (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Sys_Milliseconds () ; 
 int /*<<< orphan*/  Sys_PlatformInit () ; 
 int /*<<< orphan*/  Sys_SetDefaultInstallPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglGenBuffers ; 
 char* stub1 (int /*<<< orphan*/ ) ; 
 char const* stub2 (int /*<<< orphan*/ ) ; 
 char* stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va (char*,char const*) ; 

__attribute__((used)) static int first_start(GameContext* gc) {
  DeepmindContext* ctx = gc->dm_ctx;

  Sys_SetDefaultInstallPath(gc->runfiles_path);

  Sys_PlatformInit();
  Sys_Milliseconds();

  const char* dynamic_path = ctx->hooks.get_temporary_folder(ctx->userdata);
  Q_strcat(gc->command_line, sizeof(gc->command_line),
           va(" +set fs_temporarypath \"%s\"", dynamic_path));
  Q_strcat(gc->command_line, sizeof(gc->command_line),
           va(" +set fs_homepath \"%s\"", dynamic_path));

  Q_strcat(gc->command_line, sizeof(gc->command_line),
           va(" +set g_gametype \"%d\"", ctx->hooks.game_type(ctx->userdata)));

  const char* modifiedCommandLine =
      ctx->hooks.replace_command_line(ctx->userdata, gc->command_line);

  Com_Init((char*)modifiedCommandLine);

  NET_Init();
  CON_Init();

  // We assume PBO's are supported iff we can load the glGenBuffers function.
  gc->pbos.supported = qglGenBuffers;

  return 0;
}
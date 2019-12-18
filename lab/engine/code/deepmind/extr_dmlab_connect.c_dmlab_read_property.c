#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  (* read ) (int /*<<< orphan*/ ,char const*,char const**) ;} ;
struct TYPE_6__ {TYPE_1__ properties; } ;
struct TYPE_7__ {int /*<<< orphan*/  userdata; TYPE_2__ hooks; } ;
typedef  int /*<<< orphan*/  EnvCApi_PropertyResult ;
typedef  TYPE_3__ DeepmindContext ;

/* Variables and functions */
 int /*<<< orphan*/  EnvCApi_PropertyResult_NotFound ; 
 int /*<<< orphan*/  EnvCApi_PropertyResult_PermissionDenied ; 
 int /*<<< orphan*/  EnvCApi_PropertyResult_Success ; 
 TYPE_3__* dmlab_context () ; 
 int /*<<< orphan*/  dmlab_fps (void*) ; 
 int /*<<< orphan*/  kReservedEnginePropertyList ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char const*,char const**) ; 
 char* va (char*,int /*<<< orphan*/ ) ; 

EnvCApi_PropertyResult dmlab_read_property(void* context, const char* key,
                                           const char** value) {
  if (strncmp(key, kReservedEnginePropertyList,
              strlen(kReservedEnginePropertyList)) == 0) {
    const char* sub_key = key + strlen(kReservedEnginePropertyList);
    if (sub_key[0] == '.') {
      ++sub_key;
      if (strcmp(sub_key, "fps") == 0) {
        *value = va("%d", dmlab_fps(context));
        return EnvCApi_PropertyResult_Success;
      }
      return EnvCApi_PropertyResult_NotFound;
    } else if (sub_key[0] == '\0') {
      return EnvCApi_PropertyResult_PermissionDenied;
    }
  }
  DeepmindContext* ctx = dmlab_context();
  return ctx->hooks.properties.read(ctx->userdata, key, value);
}
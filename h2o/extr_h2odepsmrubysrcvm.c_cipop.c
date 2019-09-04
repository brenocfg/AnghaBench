#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mrb_context {TYPE_1__* ci; } ;
struct REnv {int dummy; } ;
struct TYPE_6__ {struct mrb_context* c; } ;
typedef  TYPE_2__ mrb_state ;
struct TYPE_5__ {struct REnv* env; } ;

/* Variables and functions */
 int /*<<< orphan*/  mrb_env_unshare (TYPE_2__*,struct REnv*) ; 

__attribute__((used)) static inline void
cipop(mrb_state *mrb)
{
  struct mrb_context *c = mrb->c;
  struct REnv *env = c->ci->env;

  c->ci--;
  if (env) mrb_env_unshare(mrb, env);
}
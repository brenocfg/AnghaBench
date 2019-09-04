#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct RProc {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  h2o_mruby_config_vars_t ;

/* Variables and functions */
 struct RProc* h2o_mruby_compile_code (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int compile_test(mrb_state *mrb, h2o_mruby_config_vars_t *config, char *errbuf)
{
    struct RProc *result = h2o_mruby_compile_code(mrb, config, errbuf);
    return result != NULL;
}
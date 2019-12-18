#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int write_attacks; scalar_t__ brain_attack; scalar_t__ short_alloc; int /*<<< orphan*/ * short_buf; scalar_t__ short_cnt; scalar_t__ long_alloc; int /*<<< orphan*/ * long_buf; scalar_t__ long_cnt; scalar_t__ ab; int /*<<< orphan*/  mux_ar; int /*<<< orphan*/  mux_ag; } ;
typedef  TYPE_1__ brain_server_db_attack_t ;

/* Variables and functions */
 int /*<<< orphan*/  hc_thread_mutex_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hcfree (int /*<<< orphan*/ *) ; 

void brain_server_db_attack_free (brain_server_db_attack_t *brain_server_db_attack)
{
  hc_thread_mutex_delete (brain_server_db_attack->mux_ag);
  hc_thread_mutex_delete (brain_server_db_attack->mux_ar);

  hcfree (brain_server_db_attack->long_buf);
  hcfree (brain_server_db_attack->short_buf);

  brain_server_db_attack->ab            = 0;
  brain_server_db_attack->long_cnt      = 0;
  brain_server_db_attack->long_buf      = NULL;
  brain_server_db_attack->long_alloc    = 0;
  brain_server_db_attack->short_cnt     = 0;
  brain_server_db_attack->short_buf     = NULL;
  brain_server_db_attack->short_alloc   = 0;
  brain_server_db_attack->brain_attack  = 0;
  brain_server_db_attack->write_attacks = false;
}
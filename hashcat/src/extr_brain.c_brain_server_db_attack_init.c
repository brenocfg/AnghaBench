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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int write_attacks; int /*<<< orphan*/  mux_ag; int /*<<< orphan*/  mux_ar; scalar_t__ long_alloc; int /*<<< orphan*/ * long_buf; scalar_t__ long_cnt; scalar_t__ short_alloc; int /*<<< orphan*/ * short_buf; scalar_t__ short_cnt; scalar_t__ ab; int /*<<< orphan*/  brain_attack; } ;
typedef  TYPE_1__ brain_server_db_attack_t ;

/* Variables and functions */
 int /*<<< orphan*/  hc_thread_mutex_init (int /*<<< orphan*/ ) ; 

void brain_server_db_attack_init (brain_server_db_attack_t *brain_server_db_attack, const u32 brain_attack)
{
  brain_server_db_attack->brain_attack = brain_attack;

  brain_server_db_attack->ab            = 0;
  brain_server_db_attack->short_cnt     = 0;
  brain_server_db_attack->short_buf     = NULL;
  brain_server_db_attack->short_alloc   = 0;
  brain_server_db_attack->long_cnt      = 0;
  brain_server_db_attack->long_buf      = NULL;
  brain_server_db_attack->long_alloc    = 0;
  brain_server_db_attack->write_attacks = false;

  hc_thread_mutex_init (brain_server_db_attack->mux_ar);
  hc_thread_mutex_init (brain_server_db_attack->mux_ag);
}
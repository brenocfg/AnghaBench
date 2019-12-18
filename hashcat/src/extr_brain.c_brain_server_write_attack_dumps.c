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
typedef  size_t i64 ;
typedef  int /*<<< orphan*/  file ;
struct TYPE_5__ {size_t attack_cnt; TYPE_2__* attack_buf; } ;
typedef  TYPE_1__ brain_server_dbs_t ;
struct TYPE_6__ {int brain_attack; int /*<<< orphan*/  mux_ag; } ;
typedef  TYPE_2__ brain_server_db_attack_t ;

/* Variables and functions */
 int /*<<< orphan*/  brain_server_write_attack_dump (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  hc_thread_mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hc_thread_mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,int) ; 

bool brain_server_write_attack_dumps (brain_server_dbs_t *brain_server_dbs, const char *path)
{
  for (i64 idx = 0; idx < brain_server_dbs->attack_cnt; idx++)
  {
    brain_server_db_attack_t *brain_server_db_attack = &brain_server_dbs->attack_buf[idx];

    hc_thread_mutex_lock (brain_server_db_attack->mux_ag);

    char file[100];

    memset (file, 0, sizeof (file));

    snprintf (file, sizeof (file), "%s/brain.%08x.admp", path, brain_server_db_attack->brain_attack);

    brain_server_write_attack_dump (brain_server_db_attack, file);

    hc_thread_mutex_unlock (brain_server_db_attack->mux_ag);
  }

  return true;
}
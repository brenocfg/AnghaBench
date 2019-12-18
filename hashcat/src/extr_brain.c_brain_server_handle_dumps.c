#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * brain_server_dbs; } ;
typedef  TYPE_1__ brain_server_dumper_options_t ;
typedef  int /*<<< orphan*/  brain_server_dbs_t ;

/* Variables and functions */
 int BRAIN_SERVER_DUMP_EVERY ; 
 int /*<<< orphan*/  brain_server_write_attack_dumps (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  brain_server_write_hash_dumps (int /*<<< orphan*/ *,char*) ; 
 int keep_running ; 
 int /*<<< orphan*/  sleep (int) ; 

void *brain_server_handle_dumps (void *p)
{
  brain_server_dumper_options_t *brain_server_dumper_options = (brain_server_dumper_options_t *) p;

  brain_server_dbs_t *brain_server_dbs = brain_server_dumper_options->brain_server_dbs;

  int i = 0;

  while (keep_running == true)
  {
    if (i == BRAIN_SERVER_DUMP_EVERY)
    {
      brain_server_write_hash_dumps   (brain_server_dbs, ".");
      brain_server_write_attack_dumps (brain_server_dbs, ".");

      i = 0;
    }
    else
    {
      i++;
    }

    sleep (1);
  }

  return NULL;
}
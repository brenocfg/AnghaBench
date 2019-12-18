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
struct TYPE_3__ {int write_hashes; scalar_t__ brain_session; scalar_t__ long_alloc; int /*<<< orphan*/ * long_buf; scalar_t__ long_cnt; scalar_t__ hb; int /*<<< orphan*/  mux_hr; int /*<<< orphan*/  mux_hg; } ;
typedef  TYPE_1__ brain_server_db_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  hc_thread_mutex_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hcfree (int /*<<< orphan*/ *) ; 

void brain_server_db_hash_free (brain_server_db_hash_t *brain_server_db_hash)
{
  hc_thread_mutex_delete (brain_server_db_hash->mux_hg);
  hc_thread_mutex_delete (brain_server_db_hash->mux_hr);

  hcfree (brain_server_db_hash->long_buf);

  brain_server_db_hash->hb            = 0;
  brain_server_db_hash->long_cnt      = 0;
  brain_server_db_hash->long_buf      = NULL;
  brain_server_db_hash->long_alloc    = 0;
  brain_server_db_hash->write_hashes  = false;
  brain_server_db_hash->brain_session = 0;
}
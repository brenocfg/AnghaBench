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
struct TYPE_3__ {int write_hashes; int /*<<< orphan*/  mux_hg; int /*<<< orphan*/  mux_hr; scalar_t__ long_alloc; int /*<<< orphan*/ * long_buf; scalar_t__ long_cnt; scalar_t__ hb; int /*<<< orphan*/  brain_session; } ;
typedef  TYPE_1__ brain_server_db_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  hc_thread_mutex_init (int /*<<< orphan*/ ) ; 

void brain_server_db_hash_init (brain_server_db_hash_t *brain_server_db_hash, const u32 brain_session)
{
  brain_server_db_hash->brain_session = brain_session;

  brain_server_db_hash->hb           = 0;
  brain_server_db_hash->long_cnt     = 0;
  brain_server_db_hash->long_buf     = NULL;
  brain_server_db_hash->long_alloc   = 0;
  brain_server_db_hash->write_hashes = false;

  hc_thread_mutex_init (brain_server_db_hash->mux_hr);
  hc_thread_mutex_init (brain_server_db_hash->mux_hg);
}
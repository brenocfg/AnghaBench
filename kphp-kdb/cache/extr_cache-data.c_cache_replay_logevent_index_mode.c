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
struct lev_generic {int dummy; } ;

/* Variables and functions */
 int cache_replay_logevent (struct lev_generic*,int) ; 
 int /*<<< orphan*/  cache_save_pseudo_index () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ index_timestamp ; 
 scalar_t__ log_last_ts ; 

int cache_replay_logevent_index_mode  (struct lev_generic *E, int size) {
  if (log_last_ts >= index_timestamp) {
    cache_save_pseudo_index ();
    exit (0);
  }
  return cache_replay_logevent (E, size);
}
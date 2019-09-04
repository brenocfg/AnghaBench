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
struct tl_act_extra {int flags; int size; int /*<<< orphan*/  act; } ;

/* Variables and functions */
 int TL_ENGINE_NOP ; 
 int TL_ENGINE_STAT ; 
 struct tl_act_extra* malloc (int) ; 
 int /*<<< orphan*/  memset (struct tl_act_extra*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tl_act_nop ; 
 int /*<<< orphan*/  tl_act_stat ; 
 int /*<<< orphan*/  tl_fetch_end () ; 
 scalar_t__ tl_fetch_error () ; 
 int /*<<< orphan*/  tl_fetch_int () ; 
 int tl_fetch_lookup_int () ; 

struct tl_act_extra *tl_default_parse_function (long long actor_id) {
  if (actor_id) { 
    return 0; 
  }
  int f = tl_fetch_lookup_int ();
  if (tl_fetch_error ()) {
    return 0;
  }
  if (f == TL_ENGINE_NOP) {
    tl_fetch_int ();
    tl_fetch_end ();
    if (tl_fetch_error ()) {
      return 0;
    }
    struct tl_act_extra *extra = malloc (sizeof (*extra));
    memset (extra, 0, sizeof (*extra));
    extra->flags = 3;
    extra->size = sizeof (*extra);
    extra->act = tl_act_nop;
    return extra;
  }
  if (f == TL_ENGINE_STAT) {
    tl_fetch_int ();
    tl_fetch_end ();
    if (tl_fetch_error ()) {
      return 0;
    }
    struct tl_act_extra *extra = malloc (sizeof (*extra));
    memset (extra, 0, sizeof (*extra));
    extra->flags = 3;
    extra->size = sizeof (*extra);
    extra->act = tl_act_stat;
    return extra;
  }
  return 0;
}
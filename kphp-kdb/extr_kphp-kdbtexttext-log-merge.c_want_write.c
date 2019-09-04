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
struct lev_generic {scalar_t__ a; } ;
struct lev_add_message {scalar_t__ legacy_id; int type; int date; int user_id; int peer_id; } ;
struct TYPE_2__ {scalar_t__ max_legacy_id; scalar_t__ min_legacy_id; } ;

/* Variables and functions */
 TYPE_1__ Header ; 
 int LEV_TIMESTAMP ; 
 int LEV_TX_ADD_MESSAGE ; 
 int LEV_TX_ADD_MESSAGE_LF ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,scalar_t__,int,int) ; 
 int mode ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ t_now ; 

__attribute__((used)) static int want_write (int type, void *ptr) {
  struct lev_generic *E = ptr;

  if (type == LEV_TIMESTAMP && E->a > t_now) {
    t_now = E->a;
    /*if (t_now > t_cutoff && !mode) {
      mode = 1;
      fprintf (stderr, "reached binlog time %d above cutoff time %d at read position %lld\n", t_now, t_cutoff, rd_bytes);
    }*/
  }

  if (
      (type >= LEV_TX_ADD_MESSAGE && type <= LEV_TX_ADD_MESSAGE + 0xff) ||
      (type == LEV_TX_ADD_MESSAGE_LF)
     ) {
    struct lev_add_message *EM = (struct lev_add_message *)E;

    if (!EM->legacy_id) {
      fprintf (stderr, "warning: binlog message (type=%02x, date=%d/%d, user_id=%d, peer_id=%d) has zero legacy id, ignored\n", EM->type & 0xff, EM->date, t_now, EM->user_id, EM->peer_id);
    }

    if (EM->legacy_id > Header.max_legacy_id) {
      mode |= 1;
      return 1;
    }
    if (EM->legacy_id < Header.min_legacy_id) {
      mode |= 2;
      return 2;
    }
  }

  if (type == LEV_TIMESTAMP) {
    return 1;
  }

  return 0;
}
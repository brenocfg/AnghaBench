#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  current_album_id; } ;
typedef  TYPE_1__ user ;

/* Variables and functions */
 scalar_t__ MAX_ALBUMS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  user_create_album_internal (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ user_get_albums_count (TYPE_1__*) ; 
 int /*<<< orphan*/  user_loaded (TYPE_1__*) ; 
 scalar_t__ write_only ; 

int user_create_album (user *u) {
//  dbg ("user_create_album %d\n", u->id);

  if (write_only) {
    return u->current_album_id++;
  }

  assert (user_loaded (u));

  if (user_get_albums_count (u) >= MAX_ALBUMS) {
    u->current_album_id++;
    return 0;
  }

//  dbg ("create_album (user = %d)\n", u->id);

  if (!user_create_album_internal (u, u->current_album_id)) {
    u->current_album_id++;
    return 0;
  }
  return u->current_album_id++;
}
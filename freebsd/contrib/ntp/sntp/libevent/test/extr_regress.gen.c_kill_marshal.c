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
struct kill {int how_often_length; int /*<<< orphan*/ * how_often_data; scalar_t__ how_often_set; int /*<<< orphan*/  action_data; int /*<<< orphan*/  weapon_data; } ;
struct evbuffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KILL_ACTION ; 
 int /*<<< orphan*/  KILL_HOW_OFTEN ; 
 int /*<<< orphan*/  KILL_WEAPON ; 
 int /*<<< orphan*/  evtag_marshal_int (struct evbuffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evtag_marshal_string (struct evbuffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
kill_marshal(struct evbuffer *evbuf, const struct kill *tmp){
  evtag_marshal_string(evbuf, KILL_WEAPON, tmp->weapon_data);
  evtag_marshal_string(evbuf, KILL_ACTION, tmp->action_data);
  if (tmp->how_often_set) {
    {
      int i;
      for (i = 0; i < tmp->how_often_length; ++i) {
    evtag_marshal_int(evbuf, KILL_HOW_OFTEN, tmp->how_often_data[i]);
      }
    }
  }
}
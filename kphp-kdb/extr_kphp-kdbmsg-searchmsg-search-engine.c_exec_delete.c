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
struct connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LE_DELMSG_MAGIC ; 
 int /*<<< orphan*/  LE_DELOLDMSG_MAGIC ; 
 int /*<<< orphan*/  LE_UNDELMSG_MAGIC ; 
 int /*<<< orphan*/  alloc_log_event (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delmsg_queries ; 
 int /*<<< orphan*/  dyn_delall_msg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dyn_delete_msg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dyn_undelete_msg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dyn_user_header (int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int sscanf (char*,char*,int*,int*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbosity ; 

int exec_delete (struct connection *c, char *str, int len) {
  int uid, msgid;

  while (*str == ' ') { str++; }

  if (verbosity > 0) {
    fprintf (stderr, "delete \"%s\"\n", str);
  }

  switch (*str) {

  case 'd':
    if (sscanf (str, "delmsg%d,%d ", &uid, &msgid) == 2 && uid > 0 && msgid) {
      delmsg_queries++;
      if (verbosity >= 1) {
	fprintf (stderr, "delete_msg(%d,%d)\n", uid, msgid);
      }
      alloc_log_event (LE_DELMSG_MAGIC, uid, msgid, 0);
      dyn_delete_msg (dyn_user_header (uid, 1), msgid);
      return 1;
    }
    break;

  case 'u':
    if (sscanf (str, "undelmsg%d,%d ", &uid, &msgid) == 2 && uid > 0 && msgid) {
      delmsg_queries++;
      if (verbosity >= 1) {
	fprintf (stderr, "undelete_msg(%d,%d)\n", uid, msgid);
      }
      alloc_log_event (LE_UNDELMSG_MAGIC, uid, msgid, 0);
      dyn_undelete_msg (dyn_user_header (uid, 1), msgid);
      return 1;
    }
    break;

  case 'w':
    if (sscanf (str, "wipemsg%d,%d ", &uid, &msgid) == 2 && uid > 0 && msgid) {
      delmsg_queries++;
      if (verbosity >= 1) {
	fprintf (stderr, "wipe_msg(%d,%d)\n", uid, msgid);
      }
      alloc_log_event (LE_DELOLDMSG_MAGIC, uid, msgid, 0);
      dyn_delall_msg (dyn_user_header (uid, 1), msgid);
      return 1;
    }
  }
  return 0;
}
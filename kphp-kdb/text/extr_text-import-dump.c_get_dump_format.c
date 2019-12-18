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

/* Variables and functions */
 int TF_INBOX ; 
 int TF_NONE ; 
 int TF_OUTBOX ; 
 int TF_PHOTO_COMMENTS ; 
 int TF_STATUSES ; 
 int TF_VIDEO_COMMENTS ; 
 int TF_VOTINGS ; 
 int TF_WALL ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

int get_dump_format (char *str) {
  if (!strncmp (str, "inbox", 5)) {
    return TF_INBOX;
  }
  if (!strncmp (str, "outbox", 6)) {
    return TF_OUTBOX;
  }
  if (!strncmp (str, "status", 6)) {
    return TF_STATUSES;
  }
  if (!strncmp (str, "minifeed", 8)) {
    return TF_STATUSES;
  }
  if (!strncmp (str, "wall", 4)) {
    return TF_WALL;
  }
  if (!strncmp (str, "voting", 6)) {
    return TF_VOTINGS;
  }
  if (!strncmp (str, "photos_comments", 15)) {
    return TF_PHOTO_COMMENTS;
  }
  if (!strncmp (str, "videos_comments", 15)) {
    return TF_VIDEO_COMMENTS;
  }

  return TF_NONE;
}
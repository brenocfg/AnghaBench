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
 int TF_ALBUMS_PRIV ; 
 int TF_BLOGS_PRIV ; 
 int TF_FRIENDS ; 
 int TF_MEM_PREFS ; 
 int TF_MEM_PRIV ; 
 int TF_NONE ; 
 int TF_VIDEOS_PRIV ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

int get_dump_format (char *str) {
  if (!strncmp (str, "friends", 7)) {
    return TF_FRIENDS;
  }
  if (!strncmp (str, "members_privacy", 15)) {
    return TF_MEM_PRIV;
  }
  if (!strncmp (str, "mempriv", 7)) {
    return TF_MEM_PRIV;
  }
  if (!strncmp (str, "albumpriv", 9)) {
    return TF_ALBUMS_PRIV;
  }
  if (!strncmp (str, "albums_privacy", 14)) {
    return TF_ALBUMS_PRIV;
  }
  if (!strncmp (str, "videos_privacy", 14)) {
    return TF_VIDEOS_PRIV;
  }
  if (!strncmp (str, "blog_posts_privacy", 18)) {
    return TF_BLOGS_PRIV;
  }
  if (!strncmp (str, "members_prefs", 13)) {
    return TF_MEM_PREFS;
  }

  return TF_NONE;
}
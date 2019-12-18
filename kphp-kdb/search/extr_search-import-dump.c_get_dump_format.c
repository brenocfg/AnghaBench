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
 scalar_t__ IS_PFX (char*) ; 
 int TF_APPS ; 
 int TF_AUDIO ; 
 int TF_BLOG_POSTS ; 
 int TF_EVENTS ; 
 int TF_GROUPS ; 
 int TF_MARKET_ITEMS ; 
 int TF_MEMLITE ; 
 int TF_MINIFEED ; 
 int TF_NONE ; 
 int TF_QUESTIONS ; 
 int TF_TOPICS ; 
 int TF_VIDEO ; 

int get_dump_format (char *str) {
#define IS_PFX(s)	!strncmp(str,s,sizeof(s)-1)
  if (IS_PFX("audio")) {
    return TF_AUDIO;
  }

  if (IS_PFX("video")) {
    return TF_VIDEO;
  }

  if (IS_PFX("applications")) {
    return TF_APPS;
  }

  if (IS_PFX("groups")) {
    return TF_GROUPS;
  }

  if (IS_PFX("events")) {
    return TF_EVENTS;
  }

  if (IS_PFX("blog_posts")) {
    return TF_BLOG_POSTS;
  }

  if (IS_PFX("memlite")) {
    return TF_MEMLITE;
  }

  if (IS_PFX("members_lite")) {
    return TF_MEMLITE;
  }

  if (IS_PFX("market_items")) {
    return TF_MARKET_ITEMS;
  }

  if (IS_PFX("question")) {
    return TF_QUESTIONS;
  }

  if (IS_PFX("topics")) {
    return TF_TOPICS;
  }

  if (IS_PFX("minifeed")) {
    return TF_MINIFEED;
  }

  return TF_NONE;
}
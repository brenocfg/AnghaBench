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
 int TF_APP_FANS ; 
 int TF_APP_FANS_NOTIFY ; 
 int TF_APP_FANS_SETTINGS ; 
 int TF_BANLIST ; 
 int TF_BANLISTED ; 
 int TF_BLACKLIST ; 
 int TF_BLACKLISTED ; 
 int TF_FAMILY ; 
 int TF_FAN_APPS ; 
 int TF_FAN_APPS_BALANCE ; 
 int TF_FAN_APPS_NOTIFY ; 
 int TF_FAN_APPS_SETTINGS ; 
 int TF_GROUPS_SHORT ; 
 int TF_GROUP_MEMBERS ; 
 int TF_MEMBER_GROUPS ; 
 int TF_NONE ; 
 int TF_PHOTO_REV ; 
 int TF_WIDGET_COMMENTS ; 
 int TF_WIDGET_VOTES ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

int get_dump_format (char *str) {
  if (!strncmp (str, "member_groups", 13)) {
    return TF_MEMBER_GROUPS;
  }
  if (!strncmp (str, "group_members", 13)) {
    return TF_GROUP_MEMBERS;
  }
  if (!strncmp (str, "groups_short", 12)) {
    return TF_GROUPS_SHORT;
  }
  if (!strncmp (str, "app_fans_settings", 17) || !strncmp (str, "app_members_settings", 20)) {
    return TF_APP_FANS_SETTINGS;
  }
  if (!strncmp (str, "fan_apps_settings", 17) || !strncmp (str, "member_apps_settings", 20)) {
    return TF_FAN_APPS_SETTINGS;
  }
  if (!strncmp (str, "fan_apps_balance", 16) || !strncmp (str, "member_apps_balance", 19)) {
    return TF_FAN_APPS_BALANCE;
  }
  if (!strncmp (str, "app_fans_notify", 15) || !strncmp (str, "app_members_notify", 18)) {
    return TF_APP_FANS_NOTIFY;
  }
  if (!strncmp (str, "fan_apps_notify", 15) || !strncmp (str, "member_apps_notify", 18)) {
    return TF_FAN_APPS_NOTIFY;
  }
  if (!strncmp (str, "app_fans", 8) || !strncmp (str, "app_members", 11)) {
    return TF_APP_FANS;
  }
  if (!strncmp (str, "fan_apps", 8) || !strncmp (str, "member_apps", 11)) {
    return TF_FAN_APPS;
  }
  if (!strncmp (str, "family", 6)) {
    return TF_FAMILY;
  }
  if (!strncmp (str, "widget_comments", 15)) {
    return TF_WIDGET_COMMENTS;
  }
  if (!strncmp (str, "widget_votes", 12)) {
    return TF_WIDGET_VOTES;
  }
  if (!strncmp (str, "blacklist", 10)) {
    return TF_BLACKLIST;
  }
  if (!strncmp (str, "blacklisted", 12)) {
    return TF_BLACKLISTED;
  }
  if (!strncmp (str, "banlist", 8)) {
    return TF_BANLIST;
  }
  if (!strncmp (str, "banlisted", 10)) {
    return TF_BANLISTED;
  }
  if (!strncmp (str, "photorev", 9)) {
    return TF_PHOTO_REV;
  }

  return TF_NONE;
}
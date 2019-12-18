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
struct passwd {char* pw_dir; } ;
typedef  int /*<<< orphan*/  jv ;

/* Variables and functions */
 char* getenv (char*) ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getuid () ; 
 int /*<<< orphan*/  jv_invalid_with_msg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string (char*) ; 
 int /*<<< orphan*/  jv_string_fmt (char*,char*,char*) ; 

jv get_home() {
  jv ret;
  char *home = getenv("HOME");
  if (!home) {
#ifndef WIN32
    struct passwd* pwd = getpwuid(getuid());
    if (pwd)
      ret = jv_string(pwd->pw_dir);
    else
      ret = jv_invalid_with_msg(jv_string("Could not find home directory."));
#else
    home = getenv("USERPROFILE");
    if (!home) {
      char *hd = getenv("HOMEDRIVE");
      if (!hd) hd = "";
      home = getenv("HOMEPATH");
      if (!home) {
        ret = jv_invalid_with_msg(jv_string("Could not find home directory."));
      } else {
        ret = jv_string_fmt("%s%s",hd,home);
      }
    } else {
      ret = jv_string(home);
    }
#endif
  } else {
    ret = jv_string(home);
  }
  return ret;
}
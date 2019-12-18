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
typedef  int /*<<< orphan*/  methods ;

/* Variables and functions */
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 

__attribute__((used)) static const char *
extract_method (const char *token)
{
  const char *methods[] = {
    "OPTIONS", "GET", "HEAD", "POST", "PUT",
    "DELETE", "TRACE", "CONNECT", "PATCH", "options",
    "get", "head", "post", "put", "delete",
    "trace", "connect", "patch",
    /* WebDAV */
    "PROPFIND", "PROPPATCH", "MKCOL", "COPY", "MOVE",
    "LOCK", "UNLOCK", "VERSION-CONTROL", "REPORT", "CHECKOUT",
    "CHECKIN", "UNCHECKOUT", "MKWORKSPACE", "UPDATE", "LABEL",
    "MERGE", "BASELINE-CONTROL", "MKACTIVITY", "ORDERPATCH", "propfind",
    "propwatch", "mkcol", "copy", "move", "lock",
    "unlock", "version-control", "report", "checkout", "checkin",
    "uncheckout", "mkworkspace", "update", "label", "merge",
    "baseline-control", "mkactivity", "orderpatch"
  };

  const int methods_count = sizeof (methods) / sizeof (*methods);

  int i;
  /* Length of every string in list */
  static int list_length[sizeof (methods) / sizeof (*methods)] = { -1 };
  /* Only calculate length on first time */
  if (list_length[0] == -1) {
    for (i = 0; i < methods_count; i++) {
      list_length[i] = strlen (methods[i]);
    }
  }

  for (i = 0; i < methods_count; i++) {
    if (strncmp (token, methods[i], list_length[i]) == 0) {
      return methods[i];
    }
  }
  return NULL;
}
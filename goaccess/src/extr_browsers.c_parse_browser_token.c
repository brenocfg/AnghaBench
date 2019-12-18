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
struct TYPE_2__ {int /*<<< orphan*/  browsers_hash_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL (char*,int) ; 
 int /*<<< orphan*/  LOG_INVALID (char*) ; 
 TYPE_1__ conf ; 
 scalar_t__ is_dup (char***,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  set_browser (char***,int /*<<< orphan*/ ,char*,char*) ; 
 size_t strcspn (char*,char*) ; 
 size_t strlen (char*) ; 
 size_t strspn (char*,char*) ; 
 char* trim_str (char*) ; 

__attribute__((used)) static void
parse_browser_token (char ***list, char *line, int n)
{
  char *val;
  size_t idx = 0;

  /* key */
  idx = strcspn (line, "\t");
  if (strlen (line) == idx)
    FATAL ("Malformed browser name at line: %d", n);

  line[idx] = '\0';

  /* value */
  val = line + (idx + 1);
  idx = strspn (val, "\t");
  if (strlen (val) == idx)
    FATAL ("Malformed browser category at line: %d", n);
  val = val + idx;
  val = trim_str (val);

  if (is_dup (list, conf.browsers_hash_idx, line)) {
    LOG_INVALID (("Duplicate browser entry: %s", line));
    return;
  }

  set_browser (list, conf.browsers_hash_idx, line, val);
  conf.browsers_hash_idx++;
}
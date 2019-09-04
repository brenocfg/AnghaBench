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
struct TYPE_2__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__ default_ct ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 scalar_t__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,char const*,int) ; 
 scalar_t__* remote_hostname ; 
 int sscanf (char const*,char*,int /*<<< orphan*/ *) ; 
 char* strchr (char const*,char) ; 

int parse_copyexec_results_addr (const char *s) {
  if (remote_hostname) {
    kprintf ("Command line switch -R is given more than once.\n");
    return -__LINE__;
  }

  const char *p = strchr (s, ':');
  if (p == NULL) {
    kprintf ("parse_copyexec_results_addr (%s): port isn't given.\n", s);
    return -__LINE__;
  }

  int l = p - s;
  if (sscanf (p+1, "%d", &default_ct.port) != 1) {
    kprintf ("parse_copyexec_results_addr (%s): port isn't integer.\n", s);
    return -__LINE__;
  }

  remote_hostname = malloc (l + 1);
  assert (remote_hostname != NULL);
  memcpy (remote_hostname, s, l);
  remote_hostname[l] = 0;
  return 0;
}
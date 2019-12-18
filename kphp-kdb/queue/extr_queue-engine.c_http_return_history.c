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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  http_return (struct connection*,char const*) ; 
 int /*<<< orphan*/  stderr ; 

int http_return_history (struct connection *c, const char *ans) {
  if (ans == NULL) {
    fprintf (stderr, "buffer overflow\n");
    return -500;
  }

  http_return (c, ans);

  return 0;
}
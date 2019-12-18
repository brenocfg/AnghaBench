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
struct stat_failure {int /*<<< orphan*/  size; int /*<<< orphan*/ * prog; } ;
struct connection {int dummy; } ;

/* Variables and functions */
 int return_one_key (struct connection*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stat_failure_write (struct connection *c, const char *key, struct stat_failure *S) {
  vkprintf (4, "stat_failure_write (S->prog: %s, S->size: %d)\n", S->prog, S->size);
  if (S->prog == NULL) {
    return 0;
  }
  return return_one_key (c, key, S->prog, S->size);
}
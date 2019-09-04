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
typedef  int /*<<< orphan*/  regex_t ;
typedef  int /*<<< orphan*/  err ;

/* Variables and functions */
 int /*<<< orphan*/  kprintf (char*,int,char*) ; 
 int regcomp (int /*<<< orphan*/ *,char const*,int) ; 
 int regerror (int,int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int vk_regcomp (regex_t *preg, const char *regex, int cflags) {
  char err[16384];
  int r = regcomp (preg, regex, cflags);
  if (r) {
    int l = regerror (r, preg, err, sizeof (err) - 1);
    kprintf ("%.*s\n", l, err);
  }
  return r;
}
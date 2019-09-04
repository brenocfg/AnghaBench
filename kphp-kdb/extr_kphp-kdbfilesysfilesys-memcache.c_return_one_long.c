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
 int return_one_key (struct connection*,char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,long long) ; 

__attribute__((used)) static int return_one_long (struct connection *c, const char *key, long long x) {
  static char s[32];
  return return_one_key (c, key, s, sprintf (s, "%lld", x));
}
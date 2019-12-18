#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int rm_so; int rm_eo; } ;
typedef  TYPE_1__ regmatch_t ;
typedef  int /*<<< orphan*/  regex_t ;

/* Variables and functions */
 int /*<<< orphan*/  regexec (int /*<<< orphan*/ *,char*,size_t,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void filter_re (char *text, regex_t *re) {
  regmatch_t pmatch;
  size_t nmatch = 1;
  while (!regexec (re, text, nmatch, &pmatch, 0)) {
    int j;
    for (j = pmatch.rm_so; j < pmatch.rm_eo; j++) {
      text[j] = ' ';
    }
    text += pmatch.rm_eo;
  }
}
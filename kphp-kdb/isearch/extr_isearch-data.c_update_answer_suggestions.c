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
 int A ; 
 int B ; 
 int diff ; 
 int get_pref (long long) ; 
 int /*<<< orphan*/  merge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * suggs ; 

void update_answer_suggestions (long long h, int _diff, int _A, int _B) {
  int sid = get_pref (h);
  if (sid) {
    diff = _diff;
    A = _A;
    B = _B;
    merge (suggs[sid]);
  }
}
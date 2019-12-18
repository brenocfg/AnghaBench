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
typedef  int /*<<< orphan*/  jv ;
typedef  int /*<<< orphan*/  jq_state ;

/* Variables and functions */
 int /*<<< orphan*/  jv_invalid_with_msg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string (char*) ; 

__attribute__((used)) static jv f_match(jq_state *jq, jv input, jv regex, jv modifiers, jv testmode) {
  return jv_invalid_with_msg(jv_string("jq was compiled without ONIGURUMA regex libary. match/test/sub and related functions are not available."));
}
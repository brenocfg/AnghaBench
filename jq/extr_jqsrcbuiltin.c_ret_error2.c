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

/* Variables and functions */
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_invalid_with_msg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline jv ret_error2(jv bad1, jv bad2, jv msg) {
  jv_free(bad1);
  jv_free(bad2);
  return jv_invalid_with_msg(msg);
}
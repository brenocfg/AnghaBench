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
 int time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int valid_timestamp (int timestamp) {
  static int end_timestamp = 0;
  if (!end_timestamp) {
    end_timestamp = time (NULL) + 86400;
    if (end_timestamp < 0) {
      end_timestamp = 0x7fffffff;
    }
  }
  //date -d "Jan 01 00:00:00 GMT 2006" +%s
  return 1136073600 <= timestamp && timestamp <= end_timestamp;
}
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
 scalar_t__ SPLIT_PARAM_OWNER ; 
 scalar_t__ SPLIT_PARAM_OWNERXPLACE ; 
 scalar_t__ SPLIT_PARAM_PLACE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ split_param ; 

inline int gen_split_param (int type, int owner, int place) {
  if (split_param == SPLIT_PARAM_PLACE) {
    return place;
  } else if (split_param == SPLIT_PARAM_OWNER) {
    return owner;
  } else if (split_param == SPLIT_PARAM_OWNERXPLACE) {
    return owner ^ place ^ type;
  } else {
    assert (0);
    return 0;
  }
}
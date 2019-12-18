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
#define  MPPE_POLICY_ALLOWED 129 
#define  MPPE_POLICY_REQUIRED 128 
 char const* NumStr (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
radius_policyname(int policy)
{
  switch(policy) {
  case MPPE_POLICY_ALLOWED:
    return "Allowed";
  case MPPE_POLICY_REQUIRED:
    return "Required";
  }
  return NumStr(policy, NULL, 0);
}
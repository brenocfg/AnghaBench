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
 int /*<<< orphan*/  OPIE_CHALLENGE_MAX ; 
 int /*<<< orphan*/  opierandomchallenge (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

int testrandomchallenge()
{
  char buffer[OPIE_CHALLENGE_MAX+1];

  opierandomchallenge(buffer);

  if (strncmp(buffer, "otp-", 4))
    return -1;

  return 0;
}
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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int,int) ; 
 char* hostname ; 
 scalar_t__ last_success ; 
 int next_ad_id ; 
 scalar_t__ now ; 
 int port ; 
 scalar_t__ start_time ; 
 int /*<<< orphan*/  stderr ; 

void cron (void) {
  if (now > last_success + 5 && now > start_time + 5) {
    fprintf (stderr, "fatal: no response from %s:%d in 5 seconds, exiting; %d ads processed\n", hostname, port, next_ad_id-1);
    exit (2);
  }
}
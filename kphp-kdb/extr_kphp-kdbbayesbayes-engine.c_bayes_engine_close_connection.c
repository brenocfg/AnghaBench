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
 int /*<<< orphan*/  BYS_MSG (struct connection*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msg_free (int /*<<< orphan*/ ) ; 
 int server_close_connection (struct connection*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int bayes_engine_close_connection (struct connection *c, int who) {
  if (verbosity > 1) {
    fprintf (stderr, "bayes_engine_close_connection\n");
  }
  msg_free (BYS_MSG (c));

  return server_close_connection (c, who);
}
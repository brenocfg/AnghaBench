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
struct serial {int dummy; } ;
struct hardwire_ttystate {int dummy; } ;
typedef  int /*<<< orphan*/ * serial_ttystate ;

/* Variables and functions */
 scalar_t__ get_tty_state (struct serial*,struct hardwire_ttystate*) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static serial_ttystate
hardwire_get_tty_state (struct serial *scb)
{
  struct hardwire_ttystate *state;

  state = (struct hardwire_ttystate *) xmalloc (sizeof *state);

  if (get_tty_state (scb, state))
    return NULL;

  return (serial_ttystate) state;
}
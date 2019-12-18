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
struct state {scalar_t__ (* append_char ) (struct state*,char) ;} ;

/* Variables and functions */
 int minus_flag ; 
 scalar_t__ stub1 (struct state*,char) ; 
 scalar_t__ stub2 (struct state*,unsigned char) ; 
 scalar_t__ stub3 (struct state*,char) ; 

__attribute__((used)) static int
append_char(struct state *state,
	    unsigned char arg,
	    int width,
	    int flags)
{
  while(!(flags & minus_flag) && --width > 0)
    if((*state->append_char) (state, ' '))
      return 1;

  if((*state->append_char) (state, arg))
    return 1;
  while((flags & minus_flag) && --width > 0)
    if((*state->append_char) (state, ' '))
      return 1;

  return 0;
}
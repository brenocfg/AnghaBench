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
struct state {char* s; scalar_t__ (* append_char ) (struct state*,char) ;} ;

/* Variables and functions */
 int alternate_flag ; 
 int minus_flag ; 
 int plus_flag ; 
 int space_flag ; 
 scalar_t__ stub1 (struct state*,char) ; 
 scalar_t__ stub2 (struct state*,char) ; 
 scalar_t__ stub3 (struct state*,char) ; 
 scalar_t__ stub4 (struct state*,char) ; 
 scalar_t__ stub5 (struct state*,char) ; 
 scalar_t__ stub6 (struct state*,char) ; 
 scalar_t__ stub7 (struct state*,char) ; 
 scalar_t__ stub8 (struct state*,char) ; 
 scalar_t__ stub9 (struct state*,char) ; 
 int zero_flag ; 

__attribute__((used)) static int
append_number(struct state *state,
	      unsigned long num, unsigned base, char *rep,
	      int width, int prec, int flags, int minusp)
{
  int len = 0;
  int i;

  /* given precision, ignore zero flag */
  if(prec != -1)
    flags &= ~zero_flag;
  else
    prec = 1;
  /* zero value with zero precision -> "" */
  if(prec == 0 && num == 0)
    return 0;
  do{
    if((*state->append_char)(state, rep[num % base]))
      return 1;
    len++;
    num /= base;
  }while(num);
  prec -= len;
  /* pad with prec zeros */
  while(prec-- > 0){
    if((*state->append_char)(state, '0'))
      return 1;
    len++;
  }
  /* add length of alternate prefix (added later) to len */
  if(flags & alternate_flag && (base == 16 || base == 8))
    len += base / 8;
  /* pad with zeros */
  if(flags & zero_flag){
    width -= len;
    if(minusp || (flags & space_flag) || (flags & plus_flag))
      width--;
    while(width-- > 0){
      if((*state->append_char)(state, '0'))
	return 1;
      len++;
    }
  }
  /* add alternate prefix */
  if(flags & alternate_flag && (base == 16 || base == 8)){
    if(base == 16)
      if((*state->append_char)(state, rep[10] + 23)) /* XXX */
	return 1;
    if((*state->append_char)(state, '0'))
      return 1;
  }
  /* add sign */
  if(minusp){
    if((*state->append_char)(state, '-'))
      return 1;
    len++;
  } else if(flags & plus_flag) {
    if((*state->append_char)(state, '+'))
      return 1;
    len++;
  } else if(flags & space_flag) {
    if((*state->append_char)(state, ' '))
      return 1;
    len++;
  }
  if(flags & minus_flag)
    /* swap before padding with spaces */
    for(i = 0; i < len / 2; i++){
      char c = state->s[-i-1];
      state->s[-i-1] = state->s[-len+i];
      state->s[-len+i] = c;
    }
  width -= len;
  while(width-- > 0){
    if((*state->append_char)(state,  ' '))
      return 1;
    len++;
  }
  if(!(flags & minus_flag))
    /* swap after padding with spaces */
    for(i = 0; i < len / 2; i++){
      char c = state->s[-i-1];
      state->s[-i-1] = state->s[-len+i];
      state->s[-len+i] = c;
    }

  return 0;
}
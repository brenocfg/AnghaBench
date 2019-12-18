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
typedef  unsigned char u_char ;
struct pred1_state {unsigned char* dict; size_t hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  HASH (struct pred1_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
decompress(struct pred1_state *state, u_char *source, u_char *dest, int len)
{
  int i, bitmask;
  unsigned char flags, *orgdest;

  orgdest = dest;
  while (len) {
    flags = *source++;
    len--;
    for (i = 0, bitmask = 1; i < 8; i++, bitmask <<= 1) {
      if (flags & bitmask) {
	*dest = state->dict[state->hash];	/* Guess correct */
      } else {
	if (!len)
	  break;		/* we seem to be really done -- cabo */
	state->dict[state->hash] = *source;	/* Guess wrong */
	*dest = *source++;	/* Read from source */
	len--;
      }
      HASH(state, *dest++);
    }
  }
  return (dest - orgdest);
}
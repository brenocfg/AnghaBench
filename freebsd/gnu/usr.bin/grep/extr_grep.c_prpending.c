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
 char* bufbeg ; 
 int /*<<< orphan*/  eolbyte ; 
 size_t execute (char const*,int,size_t*,int /*<<< orphan*/ ) ; 
 char const* lastout ; 
 char* memchr (char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_invert ; 
 scalar_t__ outleft ; 
 scalar_t__ pending ; 
 int /*<<< orphan*/  prline (char const*,char const*,char) ; 
 size_t stub1 (char const*,int,size_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
prpending (char const *lim)
{
  if (!lastout)
    lastout = bufbeg;
  while (pending > 0 && lastout < lim)
    {
      char const *nl = memchr (lastout, eolbyte, lim - lastout);
      size_t match_size;
      --pending;
      if (outleft
	  || (((*execute) (lastout, nl - lastout, &match_size, 0) == (size_t) -1)
	      == !out_invert))
	prline (lastout, nl + 1, '-');
      else
	pending = 0;
    }
}
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
struct parity {int set; scalar_t__ name1; scalar_t__ name; } ;

/* Variables and functions */
 scalar_t__ strcasecmp (scalar_t__,char const*) ; 
 struct parity* validparity ; 

__attribute__((used)) static int
GetParityValue(const char *str)
{
  const struct parity *pp;

  for (pp = validparity; pp->name; pp++) {
    if (strcasecmp(pp->name, str) == 0 ||
	strcasecmp(pp->name1, str) == 0) {
      return pp->set;
    }
  }
  return (-1);
}
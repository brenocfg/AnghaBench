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
struct badness_vector {int* rank; } ;
typedef  enum oload_classification { ____Placeholder_oload_classification } oload_classification ;

/* Variables and functions */
 int INCOMPATIBLE ; 
 int NON_STANDARD ; 
 int STANDARD ; 

__attribute__((used)) static enum oload_classification
classify_oload_match (struct badness_vector *oload_champ_bv,
		      int nargs,
		      int static_offset)
{
  int ix;

  for (ix = 1; ix <= nargs - static_offset; ix++)
    {
      if (oload_champ_bv->rank[ix] >= 100)
	return INCOMPATIBLE;	/* truly mismatched types */
      else if (oload_champ_bv->rank[ix] >= 10)
	return NON_STANDARD;	/* non-standard type conversions needed */
    }

  return STANDARD;		/* Only standard conversions needed.  */
}
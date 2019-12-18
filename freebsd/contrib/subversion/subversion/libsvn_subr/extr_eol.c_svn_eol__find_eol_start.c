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
typedef  int apr_uintptr_t ;
typedef  int apr_size_t ;

/* Variables and functions */
 int SVN__BIT_7_SET ; 
 int SVN__LOWER_7BITS_SET ; 
 int SVN__N_MASK ; 
 int SVN__R_MASK ; 

char *
svn_eol__find_eol_start(char *buf, apr_size_t len)
{
#if SVN_UNALIGNED_ACCESS_IS_OK

  /* Scan the input one machine word at a time. */
  for (; len > sizeof(apr_uintptr_t)
       ; buf += sizeof(apr_uintptr_t), len -= sizeof(apr_uintptr_t))
    {
      /* This is a variant of the well-known strlen test: */
      apr_uintptr_t chunk = *(const apr_uintptr_t *)buf;

      /* A byte in SVN__R_TEST is \0, iff it was \r in *BUF.
       * Similarly, SVN__N_TEST is an indicator for \n. */
      apr_uintptr_t r_test = chunk ^ SVN__R_MASK;
      apr_uintptr_t n_test = chunk ^ SVN__N_MASK;

      /* A byte in SVN__R_TEST can only be < 0x80, iff it has been \0 before
       * (i.e. \r in *BUF). Ditto for SVN__N_TEST. */
      r_test |= (r_test & SVN__LOWER_7BITS_SET) + SVN__LOWER_7BITS_SET;
      n_test |= (n_test & SVN__LOWER_7BITS_SET) + SVN__LOWER_7BITS_SET;

      /* Check whether at least one of the words contains a byte <0x80
       * (if one is detected, there was a \r or \n in CHUNK). */
      if ((r_test & n_test & SVN__BIT_7_SET) != SVN__BIT_7_SET)
        break;
    }

#endif

  /* The remaining odd bytes will be examined the naive way: */
  for (; len > 0; ++buf, --len)
    {
      if (*buf == '\n' || *buf == '\r')
        return buf;
    }

  return NULL;
}
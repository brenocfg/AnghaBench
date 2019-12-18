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
typedef  int /*<<< orphan*/  svn_boolean_t ;

/* Variables and functions */
 int APR_MD5_DIGESTSIZE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int hex_to_int (char const) ; 

__attribute__((used)) static svn_boolean_t hex_decode(unsigned char *hashval, const char *hexval)
{
  int i, h1, h2;

  for (i = 0; i < APR_MD5_DIGESTSIZE; i++)
    {
      h1 = hex_to_int(hexval[2 * i]);
      h2 = hex_to_int(hexval[2 * i + 1]);
      if (h1 == -1 || h2 == -1)
        return FALSE;
      hashval[i] = (unsigned char)((h1 << 4) | h2);
    }
  return TRUE;
}